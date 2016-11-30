// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataEtherNetDIX.h"

namespace ttop {

namespace level_data {

typename logic::Logic<ChunkEtherNetDIX>::t_string_value DataEtherNetDIX::ParseStringCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataEtherNet LogicEtherNet;
			auto subfn = LogicEtherNet.ParseString(child);
			auto r = [subfn](std::shared_ptr<ChunkEtherNetDIX> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkEtherNetDIX>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkEtherNetDIX>::t_bool_value DataEtherNetDIX::ParseBoolCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataEtherNet LogicEtherNet;
			auto subfn = LogicEtherNet.ParseBool(child);
			auto r = [subfn](std::shared_ptr<ChunkEtherNetDIX> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkEtherNetDIX>::ParseBoolCustom(elt));
}

typename logic::Logic<ChunkEtherNetDIX>::t_longlong_value DataEtherNetDIX::ParseLongLongCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataEtherNet LogicEtherNet;
			auto subfn = LogicEtherNet.ParseLongLong(child);
			auto r = [subfn](std::shared_ptr<ChunkEtherNetDIX> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkEtherNetDIX>::ParseLongLongCustom(elt));
}

DataEtherNetDIX::~DataEtherNetDIX() {};

};

};
