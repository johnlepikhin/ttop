
#ifndef SRC_LEVELS_DATASSL_H_
#define SRC_LEVELS_DATASSL_H_

#include <levels/ChunkSSL.h>

#include "../Logic.h"

namespace ttop {
namespace level_data {

class DataSSL: public logic::Logic<ChunkSSL> {
public:
	virtual typename logic::Logic<ChunkSSL>::t_string_value ParseStringCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkSSL>::t_bool_value ParseBoolCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkSSL>::t_longlong_value ParseLongLongCustom(const tinyxml2::XMLElement &elt);
};

} /* namespace level_data */
} /* namespace ttop */

#endif /* SRC_LEVELS_DATASSL_H_ */
