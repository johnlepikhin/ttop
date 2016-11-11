
#ifndef SRC_LEVELS_TCP_H_
#define SRC_LEVELS_TCP_H_

#include <levels/ParserTCP.h>

#include "Level.h"

namespace ttop {
namespace level {

class TCP : public Level<ParserTCP> {
public:
	parserDescription::info GetDescription();
	TCP();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_TCP_H_ */
