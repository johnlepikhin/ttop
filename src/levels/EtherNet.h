
#ifndef SRC_LEVELS_ETHERNET_H_
#define SRC_LEVELS_ETHERNET_H_

#include "LevelTraits.h"
#include <levels/ParserEtherNet.h>

namespace ttop {

namespace level {

class EtherNet: public LevelTraits<ParserEtherNet> {
public:
	parserDescription::info GetDescription();

	EtherNet();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNET_H_ */
