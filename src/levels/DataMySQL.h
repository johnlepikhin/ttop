
#ifndef SRC_LEVELS_DATAMYSQL_H_
#define SRC_LEVELS_DATAMYSQL_H_

#include <levels/PacketMySQL.h>

#include "../Logic.h"

namespace ttop {
namespace level_data {

class DataMySQL: public logic::Logic<PacketMySQL> {
public:
	virtual typename logic::Logic<PacketMySQL>::t_string_value ParseStringCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<PacketMySQL>::t_bool_value ParseBoolCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<PacketMySQL>::t_longlong_value ParseLongLongCustom(const tinyxml2::XMLElement &elt);
	virtual ~DataMySQL();
};

} /* namespace level_data */
} /* namespace ttop */

#endif /* SRC_LEVELS_DATAMYSQL_H_ */
