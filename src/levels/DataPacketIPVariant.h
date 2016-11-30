
#ifndef SRC_LEVELS_DATAPACKETIPVARIANT_H_
#define SRC_LEVELS_DATAPACKETIPVARIANT_H_

#include "../Logic.h"
#include "../src/levels/PacketIPVariant.h"
#include "DataPacketIPv4.h"

namespace ttop {
namespace level_data {

class DataPacketIPVariant: public logic::Logic<PacketIPVariant>
{
public:
	virtual typename logic::Logic<PacketIPVariant>::t_bool_value ParseBoolCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<PacketIPVariant>::t_string_value ParseStringCustom(const tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<PacketIPVariant>::t_longlong_value ParseLongLongCustom(const tinyxml2::XMLElement &elt);
	virtual ~DataPacketIPVariant();
};

}

}

#endif /* SRC_LEVELS_DATAPACKETIPVARIANT_H_ */
