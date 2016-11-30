// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
