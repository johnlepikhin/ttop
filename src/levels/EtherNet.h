
#ifndef SRC_LEVELS_ETHERNET_H_
#define SRC_LEVELS_ETHERNET_H_

#include "LevelTraits.h"
#include <levels/ParserEtherNet.h>
#include <memory>
#include "../Filter.h"

namespace ttop {

namespace level {

class FilterEtherNet: public ttop::logic::Filter<ChunkEtherNet>
{
public:
	virtual typename ttop::logic::Logic<ChunkEtherNet, bool>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt);
};

class EtherNet: public LevelTraits<ParserEtherNet> {
public:
	parserDescription::info GetDescription();

	EtherNet();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNET_H_ */
