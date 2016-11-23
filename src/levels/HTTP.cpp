
#include "HTTP.h"

#include "DataHTTP.h"

namespace ttop {
namespace level {

parserDescription::info HTTP::GetDescription()
{
	return (parserDescription::HTTP);
}

HTTP::HTTP()
	: Level(std::make_shared<ttop::level_data::DataHTTP>())
{
}

} /* namespace level */
} /* namespace ttop */
