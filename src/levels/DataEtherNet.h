
#ifndef SRC_LEVELS_DATAETHERNET_H_
#define SRC_LEVELS_DATAETHERNET_H_

#include "../Logic.h"
#include "levels/ChunkEtherNet.h"

namespace ttop {

namespace level_data {

class DataEtherNet: public logic::Logic<ChunkEtherNet>
{
public:
	virtual typename logic::Logic<ChunkEtherNet>::t_string_value ParseStringCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkEtherNet>::t_longlong_value ParseLongLongCustom(const tinyxml2::XMLElement &elt);
	virtual ~DataEtherNet();
};

}

}

#endif /* SRC_LEVELS_DATAETHERNET_H_ */
