// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataPacketIPVariant.h"

namespace ttop {

namespace level_data {

typename logic::Logic<PacketIPVariant>::t_bool_value DataPacketIPVariant::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "IsIPv4") {
		auto r = [](const std::shared_ptr<PacketIPVariant> &c) {
			return (c->IPv4 != nullptr);
		};
		return (r);
	} else if (name == "IsIPv6") {
		auto r = [](const std::shared_ptr<PacketIPVariant> &c) {
			return (c->IPv6 != nullptr);
		};
		return (r);
	} else if (name == "IPv4") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPv4 LogicIPv4;
			auto subfn = LogicIPv4.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<PacketIPVariant> &c) {
				return(subfn(c->IPv4));
			};
			return (r);
		}
		throw logic::ParseError("No child for <IPv4/>");
	}
	return (ttop::logic::Logic<PacketIPVariant>::ParseBoolCustom(elt));
}

typename logic::Logic<PacketIPVariant>::t_string_value DataPacketIPVariant::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "IPv4") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPv4 LogicIPv4;
			auto subfn = LogicIPv4.ParseString(child);
			auto r = [subfn](const std::shared_ptr<PacketIPVariant> &c) {
				return(subfn(c->IPv4));
			};
			return (r);
		}
		throw logic::ParseError("No child for <IPv4/>");
	}
	return (ttop::logic::Logic<PacketIPVariant>::ParseStringCustom(elt));
}

typename logic::Logic<PacketIPVariant>::t_longlong_value DataPacketIPVariant::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "IPv4") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPv4 LogicIPv4;
			auto subfn = LogicIPv4.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<PacketIPVariant> &c) {
				return(subfn(c->IPv4));
			};
			return (r);
		}
		throw logic::ParseError("No child for <IPv4/>");
	}
	return (ttop::logic::Logic<PacketIPVariant>::ParseLongLongCustom(elt));
}

DataPacketIPVariant::~DataPacketIPVariant() {};


}

}
