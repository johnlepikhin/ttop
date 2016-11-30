// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * View.cpp
 *
 *  Created on: 11 нояб. 2016 г.
 *      Author: eugene
 */

#include "View.h"
#include <iostream>
#include "../ParserDescription.h"


namespace ttop {
namespace view {

template <typename IN>
void View<IN>::Output() {};

template <typename IN>
void View<IN>::FillSelection(View<IN>::t_selection &vector, std::shared_ptr<IN> chunk) {
	for (auto it = vector.begin(); it!=vector.end(); ++it) {
		(*it).Input(chunk);
	}
}

template <typename IN>
void View<IN>::Input(std::shared_ptr<IN> chunk)
{
	Where.Input(chunk);
	Trigger.Input(chunk);

	if (Where.Val) {
		GroupBy.Input(chunk);
		auto g = Selection.find(GroupBy.Val);
		if (g == Selection.end()) {
			t_selection vector = Selection_source;
			FillSelection(vector, chunk);
			Selection.emplace(GroupBy.Val, vector);
		} else {
			FillSelection(g->second, chunk);
		}
	}

	if (Trigger.Val) {
		Output();
		Where.Reset();
		Trigger.Reset();
		GroupBy.Reset();
		Selection.clear();
	}
}

template <typename IN>
void View<IN>::ParseParams(tinyxml2::XMLElement *node) {};

template <typename IN>
void View<IN>::ParseSelects(tinyxml2::XMLElement *node) {
	tinyxml2::XMLHandle docHandle(node);
	tinyxml2::XMLElement* select = docHandle.FirstChildElement("select").ToElement();
	if (select) {
		tinyxml2::XMLNode *child = select->FirstChild();
		while (child) {
			tinyxml2::XMLElement *elt = child->ToElement();
			if (elt) {
				const char *_name = elt->Attribute("name");
				std::string name = (_name) ? _name : "";
				std::function<std::string(std::shared_ptr<IN>)> v = Parser->ParseString(elt);
				Value<IN, std::string>  s(name, v, std::string(""));
				Selection_source.push_back(s);
			}
			child = child->NextSibling();
		}
	}
}

template <typename IN>
void View<IN>::ParseWhere(tinyxml2::XMLElement *node) {
	if (tinyxml2::XMLNode *child = node->FirstChildElement("where")) {
		child = child->FirstChildElement();
		if (child) {
			tinyxml2::XMLElement *elt = child->ToElement();
			if (elt) {
				Where = Value<IN, bool>(Parser->ParseBool(elt), true);
				return;
			}
		}
		throw logic::ParseError("Bool child node required for <where/>");
	}
}

template <typename IN>
void View<IN>::ParseTrigger(tinyxml2::XMLElement *node) {
	if (tinyxml2::XMLNode *child = node->FirstChildElement("trigger")) {
		child = child->FirstChildElement();
		if (child) {
			tinyxml2::XMLElement *elt = child->ToElement();
			if (elt) {
				Trigger = Value<IN, bool>(Parser->ParseBool(elt), true);
				return;
			}
		}
		throw logic::ParseError("Bool child node required for <trigger/>");
	}
}

template <typename IN>
void View<IN>::ParseGroupBy(tinyxml2::XMLElement *node) {
	if (tinyxml2::XMLNode *child = node->FirstChildElement("groupBy")) {
		child = child->FirstChildElement();
		if (child) {
			tinyxml2::XMLElement *elt = child->ToElement();
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
			ParseParams(node);
			ParseSelects(node);
			ParseWhere(node);
			ParseTrigger(node);
			ParseGroupBy(node);
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

} /* namespace view */
} /* namespace ttop */
