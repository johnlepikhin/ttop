
#include "IPv6.h"

namespace ttop {
namespace level {

parserDescription::info IPv6::GetDescription()
{
	return (parserDescription::IPv6);
}

IPv6::IPv6()
	: Level(std::make_shared<logic::Logic<THIS_T, bool> >(true))
{
}


} /* namespace level */
} /* namespace ttop */
