// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataPacketIPv4.h"

namespace ttop {

namespace level_data {

typename logic::Logic<PacketIPv4>::t_bool_value DataPacketIPv4::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "IsComplete") {
		auto r = [](const std::shared_ptr<PacketIPv4> &c) {
			return (c->IsComplete);
		};
		return (r);
	} else if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataIPv4 LogicChunkIPv4;
			auto subfn = LogicChunkIPv4.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<PacketIPv4> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}

	return (ttop::logic::Logic<PacketIPv4>::ParseBoolCustom(elt));
}

typename logic::Logic<PacketIPv4>::t_longlong_value DataPacketIPv4::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "ReceivedSize") {
		auto r = [](const std::shared_ptr<PacketIPv4> &c) {
			return (c->ReceivedSize);
		};
		return (r);
	} else if (name == "RawIfaceLength") {
		auto r = [](const std::shared_ptr<PacketIPv4> &c) {
			return (c->RawIfaceLength);
		};
		return (r);
	} else if (name == "ExpectedSize") {
		auto r = [](const std::shared_ptr<PacketIPv4> &c) {
			return (c->ExpectedSize);
		};
		return (r);
	} else if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			level_data::DataIPv4 LogicIPv4;
			auto subfn = LogicIPv4.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<PacketIPv4> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<PacketIPv4>::ParseLongLongCustom(elt));
}

typename logic::Logic<PacketIPv4>::t_string_value DataPacketIPv4::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			level_data::DataIPv4 LogicIPv4;
			auto subfn = LogicIPv4.ParseString(child);
			auto r = [subfn](const std::shared_ptr<PacketIPv4> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<PacketIPv4>::ParseStringCustom(elt));
}

DataPacketIPv4::~DataPacketIPv4() {};


}

}
