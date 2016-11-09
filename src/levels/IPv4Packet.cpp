
#include "IPv4Packet.h"

namespace ttop {
namespace level {

parserDescription::info IPv4Packet::GetDescription()
{
	return (parserDescription::IPv4Packet);
}

IPv4Packet::IPv4Packet()
	: LevelTraits<ParserPacketIPv4>(new FilterPacketIPVariant())
{
}

} /* namespace level */
} /* namespace ttop */
