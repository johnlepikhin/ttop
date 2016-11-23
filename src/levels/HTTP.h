
#ifndef SRC_LEVELS_HTTP_H_
#define SRC_LEVELS_HTTP_H_

#include <levels/ParserHTTP.h>

#include "Level.cpp"

namespace ttop {
namespace level {

class HTTP: public Level<ParserHTTP> {
public:
	parserDescription::info GetDescription();
	HTTP();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_HTTP_H_ */
