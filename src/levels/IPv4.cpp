// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "IPv4.h"
#include "DataIPv4.h"

namespace ttop {
namespace level {

parserDescription::info IPv4::GetDescription()
{
	return (parserDescription::IPv4);
}

IPv4::IPv4() : Level<ParserIPv4>(std::make_shared<level_data::DataIPv4>())
{
}

} /* namespace level */
} /* namespace ttop */
