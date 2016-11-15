
#include "EtherNetDIX.h"
#include "DataEtherNetDIX.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetDIX::GetDescription()
{
	return (parserDescription::EtherNetDIX);
}

EtherNetDIX::EtherNetDIX()
	: Level(std::make_shared<ttop::level_data::BoolEtherNetDIX>()
			, std::make_shared<ttop::level_data::LongEtherNetDIX>()
			, std::make_shared<ttop::level_data::StringEtherNetDIX>()
			)
{
}

} /* namespace level */
} /* namespace ttop */
