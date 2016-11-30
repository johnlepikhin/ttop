// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
