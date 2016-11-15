
#include "EtherNetRAW.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetRAW::GetDescription()
{
	return (parserDescription::EtherNetRAW);
}

EtherNetRAW::EtherNetRAW()
	: Level(std::make_shared<logic::Logic<THIS_T, bool> >(true)
			, std::make_shared<logic::Logic<THIS_T, unsigned long long> >(0)
			, std::make_shared<logic::Logic<THIS_T, std::string> >("")
			)
{
}

} /* namespace level */
} /* namespace ttop */
