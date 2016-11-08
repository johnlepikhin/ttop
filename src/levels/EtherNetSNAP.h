
#ifndef SRC_LEVELS_ETHERNETSNAP_H_
#define SRC_LEVELS_ETHERNETSNAP_H_

#include <levels/ParserEtherNetSNAP.h>

#include "LevelTraits.h"

namespace ttop {
namespace level {

class EtherNetSNAP : public LevelTraits<ParserEtherNetSNAP> {
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNETSNAP_H_ */
