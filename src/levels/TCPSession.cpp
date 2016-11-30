// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TCPSession.h"
#include "DataTCPSession.h"

namespace ttop {
namespace level {

parserDescription::info TCPSession::GetDescription()
{
	return (parserDescription::TCPSession);
}

TCPSession::TCPSession()
	: Level(std::make_shared<ttop::level_data::DataTCPSession>())
{
}


} /* namespace level */
} /* namespace ttop */
