
#ifndef SRC_LEVELS_DATAPACKETIPV4_H_
#define SRC_LEVELS_DATAPACKETIPV4_H_

#include "../Logic.h"
#include "../src/levels/PacketIPv4.h"
#include "../src/levels/ChunkIPv4.h"
#include "DataIPv4.h"

namespace ttop {
namespace level_data {

template <typename OUT>
class DataPacketIPv4: public logic::Logic<PacketIPv4, OUT>
{
	OUT DefaultValue;
public:
	DataPacketIPv4(OUT defaultValue)
		: logic::Logic<PacketIPv4, OUT>(defaultValue)
		, DefaultValue(defaultValue)
	{}

	virtual typename logic::Logic<PacketIPv4, OUT>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "IsComplete") {
			auto r = [](std::shared_ptr<PacketIPv4> c) {
				return (c->IsComplete);
			};
			return (r);
		} else if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataIPv4<OUT> LogicChunkIPv4(DefaultValue);
				auto subfn = LogicChunkIPv4.ParseBool(child);
				auto r = [subfn](std::shared_ptr<PacketIPv4> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
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
		} else if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				level_data::DataIPv4<OUT> LogicIPv4(DefaultValue);
				auto subfn = LogicIPv4.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<PacketIPv4> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<PacketIPv4, OUT>::ParseLongLongCustom(elt));
	}

	virtual typename logic::Logic<PacketIPv4, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				level_data::DataIPv4<OUT> LogicIPv4(DefaultValue);
				auto subfn = LogicIPv4.ParseString(child);
				auto r = [subfn](std::shared_ptr<PacketIPv4> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<PacketIPv4, OUT>::ParseStringCustom(elt));
	}

	virtual ~DataPacketIPv4() {};
};

}

}

#endif /* SRC_LEVELS_DATAPACKETIPV4_H_ */
