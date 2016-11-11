
#include "TCPSession.h"
#include "DataTCPSession.h"

namespace ttop {
namespace level {

parserDescription::info TCPSession::GetDescription()
{
	return (parserDescription::TCPSession);
}

TCPSession::TCPSession()
	: Level(std::make_shared<ttop::level_data::FilterTCPSession>())
{
}


} /* namespace level */
} /* namespace ttop */
