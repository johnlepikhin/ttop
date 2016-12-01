
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
