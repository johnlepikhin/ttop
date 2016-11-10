
#ifndef SRC_LEVELS_DATAETHERNETDIX_H_
#define SRC_LEVELS_DATAETHERNETDIX_H_

#include "../Logic.h"
#include "../src/levels/ChunkEtherNetDIX.h"
#include "DataEtherNet.h"

namespace ttop {

namespace level_data {

template <typename OUT>
class DataEtherNetDIX: public logic::Logic<ChunkEtherNetDIX, OUT>
{
	OUT DefaultValue;
public:
	DataEtherNetDIX(OUT defaultValue) : logic::Logic<ChunkEtherNetDIX, OUT>(defaultValue) {}

	virtual typename logic::Logic<ChunkEtherNetDIX, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataEtherNet<OUT> LogicEtherNet(DefaultValue);
				auto subfn = LogicEtherNet.ParseString(child);
				auto r = [subfn](std::shared_ptr<ChunkEtherNetDIX> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkEtherNetDIX, OUT>::ParseStringCustom(elt));
	}

	virtual typename logic::Logic<ChunkEtherNetDIX, OUT>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataEtherNet<OUT> LogicEtherNet(DefaultValue);
				auto subfn = LogicEtherNet.ParseBool(child);
				auto r = [subfn](std::shared_ptr<ChunkEtherNetDIX> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkEtherNetDIX, OUT>::ParseBoolCustom(elt));
	}

	virtual typename logic::Logic<ChunkEtherNetDIX, OUT>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "Parent") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataEtherNet<OUT> LogicEtherNet(DefaultValue);
				auto subfn = LogicEtherNet.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<ChunkEtherNetDIX> c) {
					return(subfn(c->Parent));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Parent/>");
		}
		return (ttop::logic::Logic<ChunkEtherNetDIX, OUT>::ParseLongLongCustom(elt));
	}

	virtual ~DataEtherNetDIX() {};
};

class FilterEtherNetDIX : public DataEtherNetDIX<bool> {
public:
	FilterEtherNetDIX() : DataEtherNetDIX<bool>(true) {}
};

}

}

#endif /* SRC_LEVELS_DATAETHERNETDIX_H_ */
