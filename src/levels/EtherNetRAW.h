
#ifndef SRC_LEVELS_ETHERNETRAW_H_
#define SRC_LEVELS_ETHERNETRAW_H_

#include <levels/ParserEtherNetRAW.h>

#include "LevelTraits.h"

namespace ttop {
namespace level {

class EtherNetRAW : public LevelTraits<ParserEtherNetRAW> {
public:
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNETRAW_H_ */
