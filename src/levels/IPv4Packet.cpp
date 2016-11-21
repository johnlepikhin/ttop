
#include "IPv4Packet.h"
#include "DataPacketIPVariant.h"

namespace ttop {
namespace level {

parserDescription::info IPv4Packet::GetDescription()
{
	return (parserDescription::IPv4Packet);
}

IPv4Packet::IPv4Packet()
	: Level<ParserPacketIPv4>(std::make_shared<level_data::DataPacketIPVariant>())
{
}

} /* namespace level */
} /* namespace ttop */
