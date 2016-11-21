
#ifndef SRC_LEVELS_DATAPACKETIPVARIANT_H_
#define SRC_LEVELS_DATAPACKETIPVARIANT_H_

#include "../Logic.h"
#include "../src/levels/PacketIPVariant.h"
#include "DataPacketIPv4.h"

namespace ttop {
namespace level_data {

class DataPacketIPVariant: public logic::Logic<PacketIPVariant>
{
public:
	virtual typename logic::Logic<PacketIPVariant>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "IsIPv4") {
			auto r = [](std::shared_ptr<PacketIPVariant> c) {
				return (c->IPv4 != nullptr);
			};
			return (r);
		} else if (name == "IsIPv6") {
			auto r = [](std::shared_ptr<PacketIPVariant> c) {
				return (c->IPv6 != nullptr);
			};
			return (r);
		} else if (name == "IPv4") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPv4 LogicIPv4;
				auto subfn = LogicIPv4.ParseBool(child);
				auto r = [subfn](std::shared_ptr<PacketIPVariant> c) {
					return(subfn(c->IPv4));
				};
				return (r);
			}
			throw logic::ParseError("No child for <IPv4/>");
		}
		return (ttop::logic::Logic<PacketIPVariant>::ParseBoolCustom(elt));
	}

	virtual typename logic::Logic<PacketIPVariant>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "IPv4") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPv4 LogicIPv4;
				auto subfn = LogicIPv4.ParseString(child);
				auto r = [subfn](std::shared_ptr<PacketIPVariant> c) {
					return(subfn(c->IPv4));
				};
				return (r);
			}
			throw logic::ParseError("No child for <IPv4/>");
		}
		return (ttop::logic::Logic<PacketIPVariant>::ParseStringCustom(elt));
	}

	virtual typename logic::Logic<PacketIPVariant>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "IPv4") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataPacketIPv4 LogicIPv4;
				auto subfn = LogicIPv4.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<PacketIPVariant> c) {
					return(subfn(c->IPv4));
				};
				return (r);
			}
			throw logic::ParseError("No child for <IPv4/>");
		}
		return (ttop::logic::Logic<PacketIPVariant>::ParseLongLongCustom(elt));
	}

	virtual ~DataPacketIPVariant() {};
};

}

}

#endif /* SRC_LEVELS_DATAPACKETIPVARIANT_H_ */
