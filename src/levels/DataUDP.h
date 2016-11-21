
#ifndef SRC_LEVELS_DATAUDP_H_
#define SRC_LEVELS_DATAUDP_H_

#include "../Logic.h"
#include "../src/levels/ChunkUDP.h"
#include "DataPacketIPVariant.h"

namespace ttop {

namespace level_data {

class DataUDP: public logic::Logic<ChunkUDP>
{
public:
	virtual typename logic::Logic<ChunkUDP>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPVariant LogiIPVariant;
				auto subfn = LogiIPVariant.ParseString(child);
				auto r = [subfn](std::shared_ptr<ChunkUDP> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkUDP>::ParseStringCustom(elt));
	}

	virtual typename logic::Logic<ChunkUDP>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPVariant LogicIPVariant;
				auto subfn = LogicIPVariant.ParseBool(child);
				auto r = [subfn](std::shared_ptr<ChunkUDP> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkUDP>::ParseBoolCustom(elt));
	}

	virtual typename logic::Logic<ChunkUDP>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "PayloadLength") {
			auto r = [](std::shared_ptr<ChunkUDP> c) {
				return (c->PayloadLength);
			};
			return (r);
		} else if (name == "PktLength") {
			auto r = [](std::shared_ptr<ChunkUDP> c) {
				return (c->PktLength);
			};
			return (r);
		} else if (name == "DestinationPort") {
			auto r = [](std::shared_ptr<ChunkUDP> c) {
				return (c->DestinationPort);
			};
			return (r);
		} else if (name == "SourcePort") {
			auto r = [](std::shared_ptr<ChunkUDP> c) {
				return (c->SourcePort);
			};
			return (r);
		} else if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPVariant LogicIPVariant;
				auto subfn = LogicIPVariant.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<ChunkUDP> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkUDP>::ParseLongLongCustom(elt));
	}

	virtual ~DataUDP() {};
};

}

}

#endif
