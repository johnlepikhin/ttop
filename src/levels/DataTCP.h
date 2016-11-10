
#ifndef SRC_LEVELS_DATATCP_H_
#define SRC_LEVELS_DATATCP_H_

#include "../Logic.h"
#include "../src/levels/ChunkTCP.h"
#include "DataPacketIPVariant.h"

namespace ttop {

namespace level_data {

template <typename OUT>
class DataTCP: public logic::Logic<ChunkTCP, OUT>
{
	OUT DefaultValue;
public:
	DataTCP(OUT defaultValue) : logic::Logic<ChunkTCP, OUT>(defaultValue) {}

	virtual typename logic::Logic<ChunkTCP, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPVariant<OUT> LogiIPVariant(DefaultValue);
				auto subfn = LogiIPVariant.ParseString(child);
				auto r = [subfn](std::shared_ptr<ChunkTCP> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkTCP, OUT>::ParseStringCustom(elt));
	}

	virtual typename logic::Logic<ChunkTCP, OUT>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPVariant<OUT> LogicIPVariant(DefaultValue);
				auto subfn = LogicIPVariant.ParseBool(child);
				auto r = [subfn](std::shared_ptr<ChunkTCP> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		} else if (name == "FlagACK") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->FlagACK);
			};
			return (r);
		} else if (name == "FlagFIN") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->FlagFIN);
			};
			return (r);
		} else if (name == "FlagPSH") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->FlagPSH);
			};
			return (r);
		} else if (name == "FlagRST") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->FlagRST);
			};
			return (r);
		} else if (name == "FlagSYN") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->FlagSYN);
			};
			return (r);
		} else if (name == "FlagURG") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->FlagURG);
			};
			return (r);
		}
		return (ttop::logic::Logic<ChunkTCP, OUT>::ParseBoolCustom(elt));
	}

	virtual typename logic::Logic<ChunkTCP, OUT>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "PayloadLength") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->PayloadLength);
			};
			return (r);
		} else if (name == "PktLength") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->PktLength);
			};
			return (r);
		} else if (name == "DestinationPort") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->DestinationPort);
			};
			return (r);
		} else if (name == "SourcePort") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->SourcePort);
			};
			return (r);
		} else if (name == "ConfirmNumber") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->ConfirmNumber);
			};
			return (r);
		} else if (name == "HeaderLength") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->HeaderLength);
			};
			return (r);
		} else if (name == "SeqNumber") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->SeqNumber);
			};
			return (r);
		} else if (name == "WindowSize") {
			auto r = [](std::shared_ptr<ChunkTCP> c) {
				return (c->WindowSize);
			};
			return (r);
		} else if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPVariant<OUT> LogicIPVariant(DefaultValue);
				auto subfn = LogicIPVariant.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<ChunkTCP> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkTCP, OUT>::ParseLongLongCustom(elt));
	}

	virtual ~DataTCP() {};
};

class FilterTCP : public DataTCP<bool> {
public:
	FilterTCP() : DataTCP<bool>(true) {}
};

}

}

#endif
