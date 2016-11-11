
#include "UDP.h"
#include "DataUDP.h"

namespace ttop {
namespace level {

parserDescription::info UDP::GetDescription()
{
	return (parserDescription::UDP);
}

UDP::UDP()
	: Level(std::make_shared<ttop::level_data::FilterUDP>())
{
}


} /* namespace level */
} /* namespace ttop */
