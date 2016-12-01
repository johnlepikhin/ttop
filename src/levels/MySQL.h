
#ifndef SRC_LEVELS_MYSQL_H_
#define SRC_LEVELS_MYSQL_H_

#include <levels/ParserPacketMySQL.h>
#include "Level.h"

namespace ttop {
namespace level {

class MySQL: public Level<ParserPacketMySQL> {
public:
	parserDescription::info GetDescription();
	MySQL();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_MYSQL_H_ */
