
#include "EtherNet.h"
#include "types/MAC.h"
#include "DataEtherNet.h"

namespace ttop {

namespace level {

parserDescription::info EtherNet::GetDescription()
{
	return (parserDescription::EtherNet);
}

EtherNet::EtherNet()
	: Level(std::make_shared<ttop::level_data::FilterEtherNet>())
{
}

} /* namespace level */
} /* namespace ttop */
