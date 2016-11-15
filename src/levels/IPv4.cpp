
#include "IPv4.h"
#include "DataIPv4.h"

namespace ttop {
namespace level {

parserDescription::info IPv4::GetDescription()
{
	return (parserDescription::IPv4);
}

IPv4::IPv4() : Level<ParserIPv4>(std::make_shared<level_data::BoolIPv4>()
		, std::make_shared<level_data::LongIPv4>()
		, std::make_shared<level_data::StringIPv4>()
		)
{
}

} /* namespace level */
} /* namespace ttop */
