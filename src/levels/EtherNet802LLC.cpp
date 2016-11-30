// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EtherNet802LLC.h"

namespace ttop {
namespace level {

parserDescription::info EtherNet802LLC::GetDescription()
{
	return (ttop::parserDescription::EtherNet802LLC);
}

EtherNet802LLC::EtherNet802LLC()
	: Level(std::make_shared<logic::Logic<THIS_T> >())
{
}

} /* namespace level */
} /* namespace ttop */
