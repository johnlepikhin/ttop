
#include "TCP.h"
#include "DataTCP.h"

namespace ttop {
namespace level {

parserDescription::info TCP::GetDescription()
{
	return (parserDescription::TCP);
}

TCP::TCP()
	: Level(std::make_shared<ttop::level_data::DataTCP>())
{
}


} /* namespace level */
} /* namespace ttop */
