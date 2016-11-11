
#ifndef SRC_LEVELS_ETHERNET802LLC_H_
#define SRC_LEVELS_ETHERNET802LLC_H_

#include <levels/ParserEtherNet802LLC.h>

#include "Level.h"

namespace ttop {
namespace level {

class EtherNet802LLC
		: public Level<ParserEtherNet802LLC> {
public:
	parserDescription::info GetDescription();
	EtherNet802LLC();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNET802LLC_H_ */
