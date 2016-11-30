
#ifndef SRC_LEVELS_DATATCP_H_
#define SRC_LEVELS_DATATCP_H_

#include "../Logic.h"
#include "../src/levels/ChunkTCP.h"
#include "DataPacketIPVariant.h"

namespace ttop {

namespace level_data {

class DataTCP: public logic::Logic<ChunkTCP>
{
public:
	virtual typename logic::Logic<ChunkTCP>::t_string_value ParseStringCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkTCP>::t_bool_value ParseBoolCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkTCP>::t_longlong_value ParseLongLongCustom(const tinyxml2::XMLElement &elt);
	virtual ~DataTCP();
};

}

}

#endif
