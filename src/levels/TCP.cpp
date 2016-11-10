
#include "TCP.h"
#include "DataTCP.h"

namespace ttop {
namespace level {

parserDescription::info TCP::GetDescription()
{
	return (parserDescription::TCP);
}

TCP::TCP()
	: LevelTraits(new ttop::level_data::FilterTCP())
{
}


} /* namespace level */
} /* namespace ttop */
