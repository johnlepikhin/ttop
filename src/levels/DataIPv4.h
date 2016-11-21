
#ifndef SRC_LEVELS_DATAIPV4_H_
#define SRC_LEVELS_DATAIPV4_H_

#include "../Logic.h"
#include "../src/levels/ChunkIPv4.h"
#include "DataEtherNetDIX.h"

namespace ttop {
namespace level_data {

class DataIPv4: public logic::Logic<ChunkIPv4>
{
public:
	virtual typename logic::Logic<ChunkIPv4>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkIPv4>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<ChunkIPv4>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt);
	virtual ~DataIPv4();
};

}

}

#endif /* SRC_LEVELS_DATAIPV4_H_ */
