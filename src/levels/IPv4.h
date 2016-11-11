
#ifndef SRC_LEVELS_IPV4_H_
#define SRC_LEVELS_IPV4_H_

#include "Level.h"

namespace ttop {
namespace level {

class IPv4 : public Level<ParserIPv4> {
public:
	IPv4();
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_IPV4_H_ */
