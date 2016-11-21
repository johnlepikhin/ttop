
#include "EtherNetSNAP.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetSNAP::GetDescription()
{
	return (parserDescription::EtherNetSNAP);
}

EtherNetSNAP::EtherNetSNAP()
	: Level(std::make_shared<logic::Logic<THIS_T> >())
{
}

} /* namespace level */
} /* namespace ttop */
