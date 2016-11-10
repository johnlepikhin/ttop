
#ifndef SRC_LEVELS_DATAETHERNET_H_
#define SRC_LEVELS_DATAETHERNET_H_

#include "../Logic.h"
#include "../src/levels/ChunkEtherNet.h"

namespace ttop {

namespace level_data {

template <typename OUT>
class DataEtherNet: public logic::Logic<ChunkEtherNet, OUT>
{
public:
	DataEtherNet(OUT defaultValue) : logic::Logic<ChunkEtherNet, OUT>(defaultValue) {}

	virtual typename logic::Logic<ChunkEtherNet, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "SourceMAC") {
			typename ttop::logic::Logic<ChunkEtherNet, OUT>::t_string_value r = [](std::shared_ptr<ChunkEtherNet> c) {
				return (MAC::asString(c->SourceMAC));
			};
			return (r);
		} else if (name == "DestinationMAC") {
			typename ttop::logic::Logic<ChunkEtherNet, OUT>::t_string_value r = [](std::shared_ptr<ChunkEtherNet> c) {
				return (MAC::asString(c->DestinationMAC));
			};
			return (r);
		}
		return (ttop::logic::Logic<ChunkEtherNet, OUT>::ParseStringCustom(elt));
	}

	virtual ~DataEtherNet() {};
};

class FilterEtherNet : public DataEtherNet<bool> {
public:
	FilterEtherNet() : DataEtherNet<bool>(true) {}
};

}

}

#endif /* SRC_LEVELS_DATAETHERNET_H_ */
