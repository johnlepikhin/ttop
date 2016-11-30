// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataEtherNet.h"

namespace ttop {

namespace level_data {

typename logic::Logic<ChunkEtherNet>::t_string_value DataEtherNet::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "SourceMAC") {
		typename ttop::logic::Logic<ChunkEtherNet>::t_string_value r = [](const std::shared_ptr<ChunkEtherNet> &c) {
			return (MAC::asString(c->SourceMAC));
		};
		return (r);
	} else if (name == "DestinationMAC") {
		typename ttop::logic::Logic<ChunkEtherNet>::t_string_value r = [](const std::shared_ptr<ChunkEtherNet> &c) {
			return (MAC::asString(c->DestinationMAC));
		};
		return (r);
	}
	return (ttop::logic::Logic<ChunkEtherNet>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkEtherNet>::t_longlong_value DataEtherNet::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Seconds") {
		return ([](const std::shared_ptr<ChunkEtherNet> &c) {
			return (c->BaseData->Seconds);
		});
	} else if (name == "USeconds") {
		return ([](const std::shared_ptr<ChunkEtherNet> &c) {
			return (c->BaseData->USeconds);
		});
	} else if (name == "Captured") {
		return ([](const std::shared_ptr<ChunkEtherNet> &c) {
			return (c->BaseData->CoveredSize);
		});
	} else if (name == "Length") {
		return ([](const std::shared_ptr<ChunkEtherNet> &c) {
			return (c->BaseData->Length);
		});
	}
	return (ttop::logic::Logic<ChunkEtherNet>::ParseLongLongCustom(elt));
}
DataEtherNet::~DataEtherNet() {};

};

};
