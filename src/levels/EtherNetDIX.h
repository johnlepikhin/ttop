
#ifndef SRC_LEVELS_ETHERNETDIX_H_
#define SRC_LEVELS_ETHERNETDIX_H_

#include <levels/ParserEtherNetDIX.h>
#include "LevelTraits.h"

namespace ttop {
namespace level {

class EtherNetDIX : public LevelTraits<ParserEtherNetDIX> {
public:
	parserDescription::info GetDescription();

	EtherNetDIX();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNETDIX_H_ */
