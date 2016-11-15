
#include "EtherNetSNAP.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetSNAP::GetDescription()
{
	return (parserDescription::EtherNetSNAP);
}

EtherNetSNAP::EtherNetSNAP()
	: Level(std::make_shared<logic::Logic<THIS_T, bool> >(true)
			, std::make_shared<logic::Logic<THIS_T, unsigned long long> >(0)
			, std::make_shared<logic::Logic<THIS_T, std::string> >("")
			)
{
}

} /* namespace level */
} /* namespace ttop */
