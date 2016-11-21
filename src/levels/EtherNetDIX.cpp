
#include "EtherNetDIX.h"
#include "DataEtherNetDIX.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetDIX::GetDescription()
{
	return (parserDescription::EtherNetDIX);
}

EtherNetDIX::EtherNetDIX()
	: Level(std::make_shared<ttop::level_data::DataEtherNetDIX>())
{
}

} /* namespace level */
} /* namespace ttop */
