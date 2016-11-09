
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

} /* namespace level */
} /* namespace ttop */
