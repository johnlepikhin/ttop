
#ifndef SRC_LEVELS_SSL_H_
#define SRC_LEVELS_SSL_H_

#include "Level.h"
#include <levels/ParserChunkSSL.h>


namespace ttop {
namespace level {

class SSL: public Level<ParserChunkSSL> {
public:
	parserDescription::info GetDescription();
	SSL();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_SSL_H_ */
