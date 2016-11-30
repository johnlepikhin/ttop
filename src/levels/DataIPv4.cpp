// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataIPv4.h"

namespace ttop {

namespace level_data {

typename logic::Logic<ChunkIPv4>::t_bool_value DataIPv4::ParseBoolCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			level_data::DataEtherNetDIX LogicEtherNetDIX;
			auto subfn = LogicEtherNetDIX.ParseBool(child);
			auto r = [subfn](std::shared_ptr<ChunkIPv4> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkIPv4>::ParseBoolCustom(elt));
}

typename logic::Logic<ChunkIPv4>::t_string_value DataIPv4::ParseStringCustom(tinyxml2::XMLElement &elt)
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
			level_data::DataEtherNetDIX LogicEtherNetDIX;
			auto subfn = LogicEtherNetDIX.ParseString(child);
			auto r = [subfn](std::shared_ptr<ChunkIPv4> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkIPv4>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkIPv4>::t_longlong_value DataIPv4::ParseLongLongCustom(tinyxml2::XMLElement &elt)
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
			level_data::DataEtherNetDIX LogicEtherNetDIX;
			auto subfn = LogicEtherNetDIX.ParseLongLong(child);
			auto r = [subfn](std::shared_ptr<ChunkIPv4> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkIPv4>::ParseLongLongCustom(elt));
}

DataIPv4::~DataIPv4() {};


}

}
