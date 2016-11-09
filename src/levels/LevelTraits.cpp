
#include "LevelTraits.h"
#include <memory>

namespace ttop {
namespace level {

template<typename PARSER>
bool LevelTraits<PARSER>::Filter(t_value chunk)
{
	return (FilterLogic->Evaluate(chunk));
}

template<typename PARSER>
bool LevelTraits<PARSER>::BeforeRecursionHook(t_value chunk)
{
	try {
		PARSER::BeforeRecursionHook(chunk);
		return (Filter(chunk));
	} catch (...) {
		throw;
	}
}

template<typename PARSER>
void LevelTraits<PARSER>::ParseXMLSettingsFilter(tinyxml2::XMLElement *node)
{
	tinyxml2::XMLElement *logic = node->FirstChildElement();
	FilterLogic->Algorithm = FilterLogic->ParseBool(logic);
}

template<typename PARSER>
void LevelTraits<PARSER>::ParseXMLSettings(tinyxml2::XMLElement *node)
{
	tinyxml2::XMLHandle docHandle(node);
	tinyxml2::XMLElement* filter = docHandle.FirstChildElement("filter").ToElement();
	if (NULL != filter) {
		ParseXMLSettingsFilter(filter);
	}
}

template<typename PARSER>
LevelTraits<PARSER>::LevelTraits()
{
}

template<typename PARSER>
LevelTraits<PARSER>::LevelTraits(t_filter *filter)
	: FilterLogic(filter)
{
}

template class LevelTraits<ParserEtherNet>;
template class LevelTraits<ParserEtherNetDIX>;
template class LevelTraits<ParserEtherNetSNAP>;
template class LevelTraits<ParserEtherNetRAW>;
template class LevelTraits<ParserEtherNet802LLC>;

template class LevelTraits<ParserIPv4>;
template class LevelTraits<ParserIPv6>;
template class LevelTraits<ParserTCP>;
template class LevelTraits<ParserUDP>;
template class LevelTraits<ParserPacketIPv4>;
template class LevelTraits<ParserSessionTCP>;

} /* namespace level */
} /* namespace ttop */
