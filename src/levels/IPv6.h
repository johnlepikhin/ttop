
#ifndef SRC_LEVELS_IPV6_H_
#define SRC_LEVELS_IPV6_H_

#include <levels/ParserIPv6.h>

#include "Level.h"

namespace ttop {
namespace level {

class IPv6 : public Level<ParserIPv6> {
public:
	parserDescription::info GetDescription();
	IPv6();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_IPV6_H_ */
