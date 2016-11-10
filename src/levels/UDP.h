
#ifndef SRC_LEVELS_UDP_H_
#define SRC_LEVELS_UDP_H_

#include <levels/ParserUDP.h>

#include "LevelTraits.h"

namespace ttop {
namespace level {

class UDP
		: public LevelTraits<ParserUDP> {
public:
	parserDescription::info GetDescription();
	UDP();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_UDP_H_ */
