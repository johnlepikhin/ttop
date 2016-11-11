
#ifndef SRC_LEVELS_ETHERNETSNAP_H_
#define SRC_LEVELS_ETHERNETSNAP_H_

#include <levels/ParserEtherNetSNAP.h>

#include "Level.h"

namespace ttop {
namespace level {

class EtherNetSNAP : public Level<ParserEtherNetSNAP> {
public:
	parserDescription::info GetDescription();
	EtherNetSNAP();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_ETHERNETSNAP_H_ */
