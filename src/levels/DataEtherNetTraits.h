
#ifndef SRC_LEVELS_DATAETHERNETTRAITS_H_
#define SRC_LEVELS_DATAETHERNETTRAITS_H_

#include "../Logic.h"
#include "../src/levels/ChunkEtherNetTraits.h"
#include "DataEtherNet.h"

namespace ttop {

namespace level_data {

class DataEtherNetTraits: public logic::Logic<ChunkEtherNetTraits>
{
public:
	virtual typename logic::Logic<ChunkEtherNetTraits>::t_string_value ParseStringCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkEtherNetTraits>::t_bool_value ParseBoolCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkEtherNetTraits>::t_longlong_value ParseLongLongCustom(const tinyxml2::XMLElement &elt);
	virtual ~DataEtherNetTraits();
};

}

}

#endif /* SRC_LEVELS_DATAETHERNETTRAITS_H_ */
