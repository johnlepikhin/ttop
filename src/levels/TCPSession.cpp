
#include "TCPSession.h"
#include "DataTCPSession.h"

namespace ttop {
namespace level {

parserDescription::info TCPSession::GetDescription()
{
	return (parserDescription::TCPSession);
}

TCPSession::TCPSession()
	: LevelTraits(new ttop::level_data::FilterTCPSession())
{
}


} /* namespace level */
} /* namespace ttop */
