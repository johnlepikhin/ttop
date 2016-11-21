
#ifndef SRC_LEVELS_DATAETHERNETDIX_H_
#define SRC_LEVELS_DATAETHERNETDIX_H_

#include "../Logic.h"
#include "../src/levels/ChunkEtherNetDIX.h"
#include "DataEtherNet.h"

namespace ttop {

namespace level_data {

class DataEtherNetDIX: public logic::Logic<ChunkEtherNetDIX>
{
public:
	virtual typename logic::Logic<ChunkEtherNetDIX>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkEtherNetDIX>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkEtherNetDIX>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt);
	virtual ~DataEtherNetDIX();
};

}

}

#endif /* SRC_LEVELS_DATAETHERNETDIX_H_ */
