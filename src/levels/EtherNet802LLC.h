
#ifndef SRC_LEVELS_ETHERNET802LLC_H_
#define SRC_LEVELS_ETHERNET802LLC_H_

#include <levels/ParserEtherNet802LLC.h>

#include "LevelTraits.h"

namespace ttop {
namespace level {

class EtherNet802LLC
		: public LevelTraits<ParserEtherNet802LLC> {
public:
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNET802LLC_H_ */
