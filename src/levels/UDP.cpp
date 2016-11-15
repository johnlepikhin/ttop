
#include "UDP.h"
#include "DataUDP.h"

namespace ttop {
namespace level {

parserDescription::info UDP::GetDescription()
{
	return (parserDescription::UDP);
}

UDP::UDP()
	: Level(std::make_shared<ttop::level_data::BoolUDP>()
			, std::make_shared<ttop::level_data::LongUDP>()
			, std::make_shared<ttop::level_data::StringUDP>()
			)
{
}


} /* namespace level */
} /* namespace ttop */
