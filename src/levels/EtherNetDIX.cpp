
#include "EtherNetDIX.h"
#include "DataEtherNetDIX.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetDIX::GetDescription()
{
	return (parserDescription::EtherNetDIX);
}

EtherNetDIX::EtherNetDIX()
	: LevelTraits(new ttop::level_data::FilterEtherNetDIX())
{
}

} /* namespace level */
} /* namespace ttop */
