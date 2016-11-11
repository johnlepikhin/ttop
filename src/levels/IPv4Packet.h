
#ifndef SRC_LEVELS_IPV4PACKET_H_
#define SRC_LEVELS_IPV4PACKET_H_

#include <levels/ParserPacketIPv4.h>

#include "Level.h"

namespace ttop {
namespace level {

class IPv4Packet : public Level<ParserPacketIPv4> {
public:
	IPv4Packet();
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_IPV4PACKET_H_ */
