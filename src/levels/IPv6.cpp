// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "IPv6.h"

namespace ttop {
namespace level {

parserDescription::info IPv6::GetDescription()
{
	return (parserDescription::IPv6);
}

IPv6::IPv6()
	: Level(std::make_shared<logic::Logic<THIS_T> >())
{
}


} /* namespace level */
} /* namespace ttop */
