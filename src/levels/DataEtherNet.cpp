
#include "DataEtherNet.h"

namespace ttop {

namespace level_data {

typename logic::Logic<ChunkEtherNet>::t_string_value DataEtherNet::ParseStringCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "SourceMAC") {
		typename ttop::logic::Logic<ChunkEtherNet>::t_string_value r = [](std::shared_ptr<ChunkEtherNet> c) {
			return (MAC::asString(c->SourceMAC));
		};
		return (r);
	} else if (name == "DestinationMAC") {
		typename ttop::logic::Logic<ChunkEtherNet>::t_string_value r = [](std::shared_ptr<ChunkEtherNet> c) {
			return (MAC::asString(c->DestinationMAC));
		};
		return (r);
	}
	return (ttop::logic::Logic<ChunkEtherNet>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkEtherNet>::t_longlong_value DataEtherNet::ParseLongLongCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Seconds") {
		return ([](std::shared_ptr<ChunkEtherNet> c) {
			return (c->BaseData->Seconds);
		});
	} else if (name == "USeconds") {
		return ([](std::shared_ptr<ChunkEtherNet> c) {
			return (c->BaseData->USeconds);
		});
	} else if (name == "Captured") {
		return ([](std::shared_ptr<ChunkEtherNet> c) {
			return (c->BaseData->CoveredSize);
		});
	} else if (name == "Length") {
		return ([](std::shared_ptr<ChunkEtherNet> c) {
			return (c->BaseData->Length);
		});
	}
	return (ttop::logic::Logic<ChunkEtherNet>::ParseLongLongCustom(elt));
}
DataEtherNet::~DataEtherNet() {};

};

};
