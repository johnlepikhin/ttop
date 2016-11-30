// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TCP.h"
#include "DataTCP.h"

namespace ttop {
namespace level {

parserDescription::info TCP::GetDescription()
{
	return (parserDescription::TCP);
}

TCP::TCP()
	: Level(std::make_shared<ttop::level_data::DataTCP>())
{
}


} /* namespace level */
} /* namespace ttop */
