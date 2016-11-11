
#ifndef SRC_LEVELS_ETHERNETRAW_H_
#define SRC_LEVELS_ETHERNETRAW_H_

#include <levels/ParserEtherNetRAW.h>

#include "Level.h"

namespace ttop {
namespace level {

class EtherNetRAW : public Level<ParserEtherNetRAW> {
public:
	parserDescription::info GetDescription();
	EtherNetRAW();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNETRAW_H_ */
