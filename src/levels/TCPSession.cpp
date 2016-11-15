
#include "TCPSession.h"
#include "DataTCPSession.h"

namespace ttop {
namespace level {

parserDescription::info TCPSession::GetDescription()
{
	return (parserDescription::TCPSession);
}

TCPSession::TCPSession()
	: Level(std::make_shared<ttop::level_data::BoolTCPSession>()
			, std::make_shared<ttop::level_data::LongTCPSession>()
			, std::make_shared<ttop::level_data::StringTCPSession>()
			)
{
}


} /* namespace level */
} /* namespace ttop */
