
#ifndef SRC_LEVELS_DATAHTTP_H_
#define SRC_LEVELS_DATAHTTP_H_

#include <levels/ChunkHTTP.h>

#include "../Logic.h"

namespace ttop {
namespace level_data {

class DataHTTP: public logic::Logic<ChunkHTTP> {
public:
	virtual typename logic::Logic<ChunkHTTP>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkHTTP>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkHTTP>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt);
	virtual ~DataHTTP();
};

} /* namespace level_data */
} /* namespace ttop */

#endif /* SRC_LEVELS_DATAHTTP_H_ */
