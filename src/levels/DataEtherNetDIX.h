
#ifndef SRC_LEVELS_DATAETHERNETDIX_H_
#define SRC_LEVELS_DATAETHERNETDIX_H_

#include "DataEtherNetTraits.h"
#include "../src/levels/ChunkEtherNetDIX.h"

namespace ttop {
namespace level_data {

class DataEtherNetDIX: public logic::Logic<ChunkEtherNetDIX> {
public:
	DataEtherNetTraits Traits;
	virtual typename logic::Logic<ChunkEtherNetDIX>::t_string_value ParseStringCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkEtherNetDIX>::t_bool_value ParseBoolCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkEtherNetDIX>::t_longlong_value ParseLongLongCustom(const tinyxml2::XMLElement &elt);
	virtual ~DataEtherNetDIX() {};
};

} /* namespace level_data */
} /* namespace ttop */

#endif /* SRC_LEVELS_DATAETHERNETDIX_H_ */
