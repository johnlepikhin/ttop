// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "View.h"
#include <iostream>
#include "../ParserDescription.h"
#include <algorithm>
#include <functional>
#include <chrono>

namespace ttop {
namespace view {

std::mutex OutputMutex;

template <typename IN>
void View<IN>::DoOutput(const std::vector<t_selection> &output) {};

template <typename IN>
void View<IN>::Output()
{
	std::vector<t_selection> output;
	for (auto it : Selection)
		output.push_back(std::move(it.second));

	if (OrderBy >= 0) {
		std::sort(output.begin(), output.end(), [this](t_selection &left, t_selection &right) {
			t_selection *_left = &left;
			t_selection *_right = &right;
			if (OrderDesc)
				std::swap(_left, _right);
			switch (OrderType) {
			case NUMERIC:
				return (std::stoll(_left->at(OrderBy).Val) < std::stoll(_right->at(OrderBy).Val));
			case STRING:
				return (_left->at(OrderBy).Val < _right->at(OrderBy).Val);
			}
			return (false);
		});
	}

	OutputMutex.lock();
	try {
		DoOutput(output);
	} catch (...) {
		OutputMutex.unlock();
		throw;
	}
	OutputMutex.unlock();
}

template <typename IN>
void View<IN>::FillSelection(View<IN>::t_selection &vector, const std::shared_ptr<IN> &chunk) {
	for (auto it = vector.begin(); it!=vector.end(); ++it) {
		(*it).Input(chunk);
	}
}

template <typename IN>
void View<IN>::OutputAndRestart()
{
	DataMutex.lock();
	try {
		Output();
		Where.Reset();
		Trigger.Reset();
		GroupBy.Reset();
		Selection.clear();
	} catch (...) {
		DataMutex.unlock();
		throw;
	}
	DataMutex.unlock();
}

template <typename IN>
void View<IN>::Input(const std::shared_ptr<IN> &chunk, int32_t followersProcessed)
{
	DataMutex.lock();
	try {
		if ((followersProcessed > 0 && ProcessedByFollowersCondition == IF_FALSE)
				|| (followersProcessed <= 0 && ProcessedByFollowersCondition == IF_TRUE)) {
			DataMutex.unlock();
			return;
		}

		Where.Input(chunk);
		Trigger.Input(chunk);

		if (Where.Val) {
			GroupBy.Input(chunk);
			auto g = Selection.find(GroupBy.Val);
			if (g == Selection.end()) {
				t_selection vector = Selection_source;
				FillSelection(vector, chunk);
				Selection.emplace(GroupBy.Val, std::move(vector));
			} else {
				FillSelection(g->second, chunk);
			}
		}
		DataMutex.unlock();
	} catch (...) {
		DataMutex.unlock();
		throw;
	}

	if (Trigger.Val) {
		OutputAndRestart();
	}
}

template <typename IN>
void View<IN>::ParseParams(const tinyxml2::XMLElement *node)
{
}

template <typename IN>
void View<IN>::ParseLocalParams(const tinyxml2::XMLElement *node)
{
	const char *_a = node->Attribute("processedByFollowers");
	if (_a) {
		std::string a(_a);
		if (a == "true") {
			ProcessedByFollowersCondition = IF_TRUE;
		} else if (a == "false") {
			ProcessedByFollowersCondition = IF_FALSE;
		} else if (a == "no matter") {
			ProcessedByFollowersCondition = NO_MATTER;
		} else {
			throw logic::ParseError("Attribute processedByFollowers='...' expects 'true', 'false' or 'no matter'");
		}
	}
};

template <typename IN>
void View<IN>::ParseSelects(tinyxml2::XMLElement *node) {
	tinyxml2::XMLHandle docHandle(node);
	tinyxml2::XMLElement* select = docHandle.FirstChildElement("select").ToElement();
	if (select) {
		const tinyxml2::XMLNode *child = select->FirstChild();
		int pos=0;
		while (child) {
			const tinyxml2::XMLElement *elt = child->ToElement();
			if (elt) {
				const char *_name = elt->Attribute("name");
				std::string name = (_name) ? _name : "";
				std::function<std::string(std::shared_ptr<IN>)> v = Parser->ParseString(elt);
				Value<IN, std::string>  s(name, v, std::string(""));
				Selection_source.push_back(s);

				const char *_order = elt->Attribute("order");
				if (_order) {
					std::string order(_order);
					OrderBy = pos;
					if (order == "numeric") {
						OrderType = NUMERIC;
					} else if (order == "string") {
						OrderType = STRING;
					} else {
						throw logic::ParseError("Invalid order type: '" + order + "'");
					}
				}

				const char *_orderDesc = elt->Attribute("orderDesc");
				if (_orderDesc && std::string(_orderDesc) == "true")
					OrderDesc = true;
			}
			child = child->NextSibling();
			pos++;
		}
	}
}

template <typename IN>
void View<IN>::ParseWhere(const tinyxml2::XMLElement *node) {
	if (const tinyxml2::XMLNode *child = node->FirstChildElement("where")) {
		child = child->FirstChildElement();
		if (child) {
			const tinyxml2::XMLElement *elt = child->ToElement();
			if (elt) {
				Where = Value<IN, bool>(Parser->ParseBool(elt), true);
				return;
			}
		}
		throw logic::ParseError("Bool child node required for <where/>");
	}
}

template <typename IN>
void View<IN>::TimeIntervalTrigger()
{
	while (true) {
		uint16_t sleep_for = (TimeInterval) ? TimeInterval : 1;
		std::this_thread::sleep_for(std::chrono::seconds(sleep_for));

		if (TimeInterval)
			OutputAndRestart();
	}
}

template <typename IN>
void View<IN>::ParseTrigger(const tinyxml2::XMLElement *node) {
	TimeIntervalThread = std::thread( [=] { TimeIntervalTrigger(); } );
	TimeIntervalThread.detach();

	if (const tinyxml2::XMLElement *child = node->FirstChildElement("trigger")) {
		const char *_timeInterval = child->Attribute("timeInterval");
		if (_timeInterval) {
			try {
				TimeInterval = std::stoi(_timeInterval);

			} catch (...) {
				throw logic::ParseError("Interger value (in seconds) required for <trigger timeInterval=...>");
			}
		}

		child = child->FirstChildElement();
		if (child) {
			const tinyxml2::XMLElement *elt = child->ToElement();
			if (elt) {
				Trigger = Value<IN, bool>(Parser->ParseBool(elt), true);
				return;
			}
		}
		throw logic::ParseError("Bool child node required for <trigger/>");
	}
}

template <typename IN>
void View<IN>::ParseGroupBy(const tinyxml2::XMLElement *node) {
	if (const tinyxml2::XMLNode *child = node->FirstChildElement("groupBy")) {
		child = child->FirstChildElement();
		if (child) {
			const tinyxml2::XMLElement *elt = child->ToElement();
			if (elt) {
				GroupBy = Value<IN, std::string>(Parser->ParseString(elt), "");
				return;
			}
		}
		throw logic::ParseError("Bool child node required for <groupBy/>");
	}
}

template <typename IN>
void View<IN>::Parse(tinyxml2::XMLElement *node, std::string &type)
{
	const char *_type = node->Attribute("type");
	if (_type) {
		if (TypeID() == _type) {
			ParseSelects(node);
			ParseWhere(node);
			ParseTrigger(node);
			ParseGroupBy(node);
			ParseLocalParams(node);
			ParseParams(node);
		} else {
			throw std::invalid_argument("unknown view type");
		}
	} else {
		throw logic::ParseError("type= is required for <view/>");
	}
}

template <typename IN>
View<IN>::View(std::shared_ptr<logic::Logic<IN> > parser)
	: Parser(parser)
{
}

template <typename IN>
View<IN>::~View() {}

template class View<ChunkEtherNet>;
template class View<ChunkEtherNetDIX>;
template class View<ChunkEtherNetSNAP>;
template class View<ChunkEtherNetRAW>;
template class View<ChunkEtherNet802LLC>;

template class View<ChunkIPv4>;
template class View<ChunkIPv6>;
template class View<ChunkTCP>;
template class View<ChunkUDP>;
template class View<PacketIPv4>;
template class View<PacketIPVariant>;
template class View<SessionTCP>;
template class View<EndPoint>;
template class View<ChunkHTTP>;
template class View<PacketMySQL>;
template class View<ChunkSSL>;

} /* namespace view */
} /* namespace ttop */
