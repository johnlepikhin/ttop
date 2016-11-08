
#include "EtherNet.h"
#include "types/MAC.h"

namespace ttop {

namespace level {

parserDescription::info EtherNet::GetDescription()
{
	return (parserDescription::EtherNet);
}

EtherNet::EtherNet()
{
	FilterLogic = std::unique_ptr<FilterEtherNet>(new FilterEtherNet());
}

ttop::logic::Logic<ChunkEtherNet, bool>::t_string_value FilterEtherNet::ParseStringCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "SourceMAC") {
		ttop::logic::Filter<ChunkEtherNet>::t_string_value r = [](std::shared_ptr<ChunkEtherNet> c) {
			return (MAC::asString(c->SourceMAC));
		};
		return (r);
	} else if (name == "DestinationMAC") {
		ttop::logic::Filter<ChunkEtherNet>::t_string_value r = [](std::shared_ptr<ChunkEtherNet> c) {
			return (MAC::asString(c->DestinationMAC));
		};
		return (r);
	}
	return (ttop::logic::Filter<ChunkEtherNet>::ParseStringCustom(elt));
}

} /* namespace level */
} /* namespace ttop */
