
#ifndef SRC_LEVELS_ETHERNET_H_
#define SRC_LEVELS_ETHERNET_H_

#include "levels/ParserEtherNet.h"
#include "Level.h"

namespace ttop {

namespace level {

class EtherNet: public Level<ParserEtherNet> {
public:
	parserDescription::info GetDescription();

	EtherNet();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNET_H_ */
