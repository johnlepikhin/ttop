
#include "EtherNet802LLC.h"

namespace ttop {
namespace level {

parserDescription::info EtherNet802LLC::GetDescription()
{
	return (ttop::parserDescription::EtherNet802LLC);
}

EtherNet802LLC::EtherNet802LLC()
	: Level(std::make_shared<logic::Logic<THIS_T, bool> >(true)
			, std::make_shared<logic::Logic<THIS_T, unsigned long long> >(0)
			, std::make_shared<logic::Logic<THIS_T, std::string> >("")
			)
{
}

} /* namespace level */
} /* namespace ttop */
