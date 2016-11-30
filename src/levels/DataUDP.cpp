// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataUDP.h"

namespace ttop {

namespace level_data {

typename logic::Logic<ChunkUDP>::t_string_value DataUDP::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPVariant LogiIPVariant;
			auto subfn = LogiIPVariant.ParseString(child);
			auto r = [subfn](const std::shared_ptr<ChunkUDP> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkUDP>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkUDP>::t_bool_value DataUDP::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPVariant LogicIPVariant;
			auto subfn = LogicIPVariant.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<ChunkUDP> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkUDP>::ParseBoolCustom(elt));
}

typename logic::Logic<ChunkUDP>::t_longlong_value DataUDP::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "PayloadLength") {
		auto r = [](const std::shared_ptr<ChunkUDP> &c) {
			return (c->PayloadLength);
		};
		return (r);
	} else if (name == "PktLength") {
		auto r = [](const std::shared_ptr<ChunkUDP> &c) {
			return (c->PktLength);
		};
		return (r);
	} else if (name == "DestinationPort") {
		auto r = [](const std::shared_ptr<ChunkUDP> &c) {
			return (c->DestinationPort);
		};
		return (r);
	} else if (name == "SourcePort") {
		auto r = [](const std::shared_ptr<ChunkUDP> &c) {
			return (c->SourcePort);
		};
		return (r);
	} else if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPVariant LogicIPVariant;
			auto subfn = LogicIPVariant.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<ChunkUDP> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkUDP>::ParseLongLongCustom(elt));
}

DataUDP::~DataUDP() {};


}

}
