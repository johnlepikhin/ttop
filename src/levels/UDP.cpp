// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "UDP.h"
#include "DataUDP.h"

namespace ttop {
namespace level {

parserDescription::info UDP::GetDescription()
{
	return (parserDescription::UDP);
}

UDP::UDP()
	: Level(std::make_shared<ttop::level_data::DataUDP>())
{
}


} /* namespace level */
} /* namespace ttop */
