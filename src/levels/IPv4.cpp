
#include "IPv4.h"
#include "DataIPv4.h"

namespace ttop {
namespace level {

parserDescription::info IPv4::GetDescription()
{
	return (parserDescription::IPv4);
}

IPv4::IPv4() : LevelTraits<ParserIPv4>(new level_data::FilterIPv4())
{
}

} /* namespace level */
} /* namespace ttop */
