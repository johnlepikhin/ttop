
#include "IPv6.h"

namespace ttop {
namespace level {

parserDescription::info IPv6::GetDescription()
{
	return (parserDescription::IPv6);
}

IPv6::IPv6()
	: Level(std::make_shared<logic::Logic<THIS_T, bool> >(true)
			, std::make_shared<logic::Logic<THIS_T, unsigned long long> >(0)
			, std::make_shared<logic::Logic<THIS_T, std::string> >("")
			)
{
}


} /* namespace level */
} /* namespace ttop */
