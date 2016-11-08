
#ifndef SRC_LEVELS_IPV4PACKET_H_
#define SRC_LEVELS_IPV4PACKET_H_

#include <levels/ParserPacketIPv4.h>

#include "LevelTraits.h"

namespace ttop {
namespace level {

class IPv4Packet : public LevelTraits<ParserPacketIPv4> {
public:
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_IPV4PACKET_H_ */
