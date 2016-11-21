
#ifndef SRC_LEVELS_DATAUDP_H_
#define SRC_LEVELS_DATAUDP_H_

#include "../Logic.h"
#include "../src/levels/ChunkUDP.h"
#include "DataPacketIPVariant.h"

namespace ttop {

namespace level_data {

class DataUDP: public logic::Logic<ChunkUDP>
{
public:
	virtual typename logic::Logic<ChunkUDP>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkUDP>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkUDP>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt);
	virtual ~DataUDP();
};

}

}

#endif
