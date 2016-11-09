
#include "EtherNet.h"
#include "types/MAC.h"

namespace ttop {

namespace level {

parserDescription::info EtherNet::GetDescription()
{
	return (parserDescription::EtherNet);
}

EtherNet::EtherNet()
	: LevelTraits(new FilterEtherNet())
{
}

} /* namespace level */
} /* namespace ttop */
