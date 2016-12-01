// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MySQL.h"
#include "DataMySQL.h"

namespace ttop {
namespace level {

parserDescription::info MySQL::GetDescription()
{
	return (parserDescription::MySQL);
}

MySQL::MySQL()
	: Level(std::make_shared<ttop::level_data::DataMySQL>())
{
}

} /* namespace level */
} /* namespace ttop */
