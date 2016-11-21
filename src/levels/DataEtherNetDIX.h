
#ifndef SRC_LEVELS_DATAETHERNETDIX_H_
#define SRC_LEVELS_DATAETHERNETDIX_H_

#include "../Logic.h"
#include "../src/levels/ChunkEtherNetDIX.h"
#include "DataEtherNet.h"

namespace ttop {

namespace level_data {

class DataEtherNetDIX: public logic::Logic<ChunkEtherNetDIX>
{
public:
	virtual typename logic::Logic<ChunkEtherNetDIX>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
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

	virtual typename logic::Logic<ChunkEtherNetDIX>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
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

	virtual typename logic::Logic<ChunkEtherNetDIX>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
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

	virtual ~DataEtherNetDIX() {};
};

}

}

#endif /* SRC_LEVELS_DATAETHERNETDIX_H_ */
