
#ifndef SRC_LEVELS_TCPSESSION_H_
#define SRC_LEVELS_TCPSESSION_H_

#include <levels/ParserSessionTCP.h>

#include "LevelTraits.h"

namespace ttop {
namespace level {

class TCPSession
		: public LevelTraits<ParserSessionTCP> {
public:
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_TCPSESSION_H_ */
