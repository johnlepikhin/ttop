// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SSL.h"
#include "DataSSL.h"

namespace ttop {
namespace level {

parserDescription::info SSL::GetDescription()
{
	return (parserDescription::SSL);
}

SSL::SSL()
	: Level(std::make_shared<ttop::level_data::DataSSL>())
{
}

} /* namespace level */
} /* namespace ttop */
