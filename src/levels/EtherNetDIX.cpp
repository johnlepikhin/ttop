// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EtherNetDIX.h"

#include "DataEtherNetDIX.h"

namespace ttop {
namespace level {

parserDescription::info EtherNetDIX::GetDescription()
{
	return (parserDescription::EtherNetTraits);
}

EtherNetDIX::EtherNetDIX()
	: Level(std::make_shared<ttop::level_data::DataEtherNetDIX>())
{
}

} /* namespace level */
} /* namespace ttop */
