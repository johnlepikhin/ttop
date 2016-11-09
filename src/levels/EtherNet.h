
#ifndef SRC_LEVELS_ETHERNET_H_
#define SRC_LEVELS_ETHERNET_H_

#include "LevelTraits.h"
#include <levels/ParserEtherNet.h>
#include <memory>
#include "../Logic.h"

namespace ttop {

namespace level {

template <typename OUT>
class IfDataEtherNet: public logic::Logic<ChunkEtherNet, OUT>
{
public:
	IfDataEtherNet(OUT defaultValue) : logic::Logic<ChunkEtherNet, OUT>(defaultValue) {}

	virtual typename logic::Logic<ChunkEtherNet, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "SourceMAC") {
			typename ttop::logic::Logic<ChunkEtherNet, OUT>::t_string_value r = [](std::shared_ptr<ChunkEtherNet> c) {
				return (MAC::asString(c->SourceMAC));
			};
			return (r);
		} else if (name == "DestinationMAC") {
			typename ttop::logic::Logic<ChunkEtherNet, OUT>::t_string_value r = [](std::shared_ptr<ChunkEtherNet> c) {
				return (MAC::asString(c->DestinationMAC));
			};
			return (r);
		}
		return (ttop::logic::Logic<ChunkEtherNet, OUT>::ParseStringCustom(elt));
	}

	virtual ~IfDataEtherNet() {};
};

class FilterEtherNet : public IfDataEtherNet<bool> {
public:
	FilterEtherNet() : IfDataEtherNet<bool>(true) {}
};

class EtherNet: public LevelTraits<ParserEtherNet> {
public:
	parserDescription::info GetDescription();

	EtherNet();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNET_H_ */
