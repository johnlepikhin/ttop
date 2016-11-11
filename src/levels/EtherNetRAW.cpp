
#include "EtherNetRAW.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetRAW::GetDescription()
{
	return (parserDescription::EtherNetRAW);
}

EtherNetRAW::EtherNetRAW()
	: Level(std::make_shared<logic::Logic<THIS_T, bool> >(true))
{
}

} /* namespace level */
} /* namespace ttop */
