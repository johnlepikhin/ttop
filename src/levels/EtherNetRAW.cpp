// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EtherNetRAW.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetRAW::GetDescription()
{
	return (parserDescription::EtherNetRAW);
}

EtherNetRAW::EtherNetRAW()
	: Level(std::make_shared<logic::Logic<THIS_T> >())
{
}

} /* namespace level */
} /* namespace ttop */
