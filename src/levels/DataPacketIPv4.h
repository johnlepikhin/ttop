
#ifndef SRC_LEVELS_DATAPACKETIPV4_H_
#define SRC_LEVELS_DATAPACKETIPV4_H_

#include "../Logic.h"
#include "../src/levels/PacketIPv4.h"
#include "../src/levels/ChunkIPv4.h"
#include "DataIPv4.h"

namespace ttop {
namespace level_data {

class DataPacketIPv4: public logic::Logic<PacketIPv4>
{
public:
	virtual typename logic::Logic<PacketIPv4>::t_bool_value ParseBoolCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<PacketIPv4>::t_longlong_value ParseLongLongCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<PacketIPv4>::t_string_value ParseStringCustom(const tinyxml2::XMLElement &elt);
	virtual ~DataPacketIPv4();
};

}

}

#endif /* SRC_LEVELS_DATAPACKETIPV4_H_ */
