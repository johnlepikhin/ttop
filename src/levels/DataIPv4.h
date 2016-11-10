
#ifndef SRC_LEVELS_DATAIPV4_H_
#define SRC_LEVELS_DATAIPV4_H_

#include "../Logic.h"
#include "../src/levels/ChunkIPv4.h"
#include "DataEtherNetDIX.h"

namespace ttop {
namespace level_data {

template <typename OUT>
class DataIPv4: public logic::Logic<ChunkIPv4, OUT>
{
	OUT DefaultValue;
public:
	DataIPv4(OUT defaultValue) : logic::Logic<ChunkIPv4, OUT>(defaultValue) {}

	virtual typename logic::Logic<ChunkIPv4, OUT>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				level_data::DataEtherNetDIX<OUT> LogicEtherNetDIX(DefaultValue);
				auto subfn = LogicEtherNetDIX.ParseBool(child);
				auto r = [subfn](std::shared_ptr<ChunkIPv4> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkIPv4, OUT>::ParseBoolCustom(elt));
	}

	virtual typename logic::Logic<ChunkIPv4, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "SourceIP") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (IPv4Addr::asString(c->SrcIP));
			};
			return (r);
		} else if (name == "DestinationIP") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (IPv4Addr::asString(c->DstIP));
			};
			return (r);
		} else if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				level_data::DataEtherNetDIX<OUT> LogicEtherNetDIX(DefaultValue);
				auto subfn = LogicEtherNetDIX.ParseString(child);
				auto r = [subfn](std::shared_ptr<ChunkIPv4> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkIPv4, OUT>::ParseStringCustom(elt));
	}

	virtual typename logic::Logic<ChunkIPv4, OUT>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "IHL") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->IHL32bit);
			};
			return (r);
		} else if (name == "PktLength") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->PktLength);
			};
			return (r);
		} else if (name == "PayloadLength") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->PayloadLength);
			};
			return (r);
		} else if (name == "Protocol") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->Protocol);
			};
			return (r);
		} else if (name == "ID") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->ID);
			};
			return (r);
		} else if (name == "FragmentOffset") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->FragmentOffset);
			};
			return (r);
		} else if (name == "TTL") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->TTL);
			};
			return (r);
		} else if (name == "SourceIP") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->SrcIP);
			};
			return (r);
		} else if (name == "DestinationIP") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->DstIP);
			};
			return (r);
		} else if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				level_data::DataEtherNetDIX<OUT> LogicEtherNetDIX(DefaultValue);
				auto subfn = LogicEtherNetDIX.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<ChunkIPv4> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkIPv4, OUT>::ParseLongLongCustom(elt));
	}

	virtual ~DataIPv4() {};
};

class FilterIPv4 : public DataIPv4<bool> {
public:
	FilterIPv4() : DataIPv4<bool>(true) {}
};

}

}

#endif /* SRC_LEVELS_DATAIPV4_H_ */
