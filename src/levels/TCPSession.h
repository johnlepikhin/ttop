
#ifndef SRC_LEVELS_TCPSESSION_H_
#define SRC_LEVELS_TCPSESSION_H_

#include <levels/ParserSessionTCP.h>

#include "Level.h"

namespace ttop {
namespace level {

class TCPSession
		: public Level<ParserSessionTCP> {
public:
	parserDescription::info GetDescription();
	TCPSession();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_TCPSESSION_H_ */
