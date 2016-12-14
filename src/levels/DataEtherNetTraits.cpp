// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataEtherNetTraits.h"

namespace ttop {

namespace level_data {

typename logic::Logic<ChunkEtherNetTraits>::t_string_value DataEtherNetTraits::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataEtherNet LogicEtherNet;
			auto subfn = LogicEtherNet.ParseString(child);
			auto r = [subfn](const std::shared_ptr<ChunkEtherNetTraits> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkEtherNetTraits>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkEtherNetTraits>::t_bool_value DataEtherNetTraits::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataEtherNet LogicEtherNet;
			auto subfn = LogicEtherNet.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<ChunkEtherNetTraits> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkEtherNetTraits>::ParseBoolCustom(elt));
}

typename logic::Logic<ChunkEtherNetTraits>::t_longlong_value DataEtherNetTraits::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataEtherNet LogicEtherNet;
			auto subfn = LogicEtherNet.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<ChunkEtherNetTraits> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkEtherNetTraits>::ParseLongLongCustom(elt));
}

DataEtherNetTraits::~DataEtherNetTraits() {};

};

};
