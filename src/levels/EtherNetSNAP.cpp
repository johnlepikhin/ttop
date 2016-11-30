// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EtherNetSNAP.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetSNAP::GetDescription()
{
	return (parserDescription::EtherNetSNAP);
}

EtherNetSNAP::EtherNetSNAP()
	: Level(std::make_shared<logic::Logic<THIS_T> >())
{
}

} /* namespace level */
} /* namespace ttop */
