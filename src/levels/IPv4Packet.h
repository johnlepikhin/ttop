
#ifndef SRC_LEVELS_IPV4PACKET_H_
#define SRC_LEVELS_IPV4PACKET_H_

#include <levels/ParserPacketIPv4.h>

#include "LevelTraits.h"

namespace ttop {
namespace level {

template <typename OUT>
class IfDataPacketIPv4: public logic::Logic<PacketIPv4, OUT>
{
public:
	IfDataPacketIPv4(OUT defaultValue) : logic::Logic<PacketIPv4, OUT>(defaultValue) {}

	virtual typename logic::Logic<PacketIPv4, OUT>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "IsComplete") {
			auto r = [](std::shared_ptr<PacketIPv4> c) {
				return (c->IsComplete);
			};
			return (r);
		}
		return (ttop::logic::Logic<PacketIPv4, OUT>::ParseBoolCustom(elt));
	}

	virtual typename logic::Logic<PacketIPv4, OUT>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "ReceivedSize") {
			auto r = [](std::shared_ptr<PacketIPv4> c) {
				return (c->ReceivedSize);
			};
			return (r);
		} else if (name == "RawIfaceLength") {
			auto r = [](std::shared_ptr<PacketIPv4> c) {
				return (c->RawIfaceLength);
			};
			return (r);
		} else if (name == "ExpectedSize") {
			auto r = [](std::shared_ptr<PacketIPv4> c) {
				return (c->ExpectedSize);
			};
			return (r);
		}
		return (ttop::logic::Logic<PacketIPv4, OUT>::ParseLongLongCustom(elt));
	}

	virtual ~IfDataPacketIPv4() {};
};

template <typename OUT>
class IfDataPacketIPVariant: public logic::Logic<PacketIPVariant, OUT>
{
	OUT DefaultValue;
public:
	IfDataPacketIPVariant(OUT defaultValue)
		: logic::Logic<PacketIPVariant, OUT>(defaultValue)
		, DefaultValue(defaultValue)
	{
	}

	virtual typename logic::Logic<PacketIPVariant, OUT>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
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
				IfDataPacketIPv4<OUT> LogicIPv4(DefaultValue);
				auto subfn = LogicIPv4.ParseBool(child);
				auto r = [subfn](std::shared_ptr<PacketIPVariant> c) {
					return(subfn(c->IPv4));
				};
				return (r);
			}
			throw logic::ParseError("No child for <IPv4/>");
		}
		return (ttop::logic::Logic<PacketIPVariant, OUT>::ParseBoolCustom(elt));
	}

	virtual ~IfDataPacketIPVariant() {};
};

class FilterPacketIPVariant : public IfDataPacketIPVariant<bool> {
public:
	FilterPacketIPVariant() : IfDataPacketIPVariant<bool>(true) {}
};


class IPv4Packet : public LevelTraits<ParserPacketIPv4> {
public:
	IPv4Packet();
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_IPV4PACKET_H_ */
