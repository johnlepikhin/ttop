
#include "Level.h"

#include <memory>
#include "../view/Dump.h"
#include "../view/View.h"

namespace ttop {
namespace level {

template<typename PARSER>
bool Level<PARSER>::Filter(t_value chunk)
{
	return (FilterAlgorithm(chunk));
}

template<typename PARSER>
bool Level<PARSER>::BeforeRecursionHook(t_value chunk)
{
	try {
		PARSER::BeforeRecursionHook(chunk);
		bool r = Filter(chunk);

		for (auto view : Views) {
			view->Input(chunk);
		}

		return (r);
	} catch (...) {
		throw;
	}
}

template<typename PARSER>
void Level<PARSER>::ParseXMLSettingsFilter(tinyxml2::XMLElement *node)
{
	tinyxml2::XMLElement *logic = node->FirstChildElement();
	FilterAlgorithm = BoolLogicParser->ParseBool(logic);
}

template<typename PARSER>
void Level<PARSER>::ParseXMLSettingsView(tinyxml2::XMLElement *node)
{
	const char *_type = node->Attribute("type");
	if (_type) {
		std::string type(_type);
		// TODO
		std::shared_ptr<view::View<THIS_T> > View
			= std::make_shared<view::Dump<THIS_T> >(BoolLogicParser, LongLogicParser, StringLogicParser);
		View->Parse(node, type);
		Views.push_back(View);
	} else {
		throw logic::ParseError("type= is required for <view/>");
	}
}

template<typename PARSER>
void Level<PARSER>::ParseXMLSettings(tinyxml2::XMLElement *node)
{
	tinyxml2::XMLHandle docHandle(node);
	tinyxml2::XMLElement* filter = docHandle.FirstChildElement("filter").ToElement();
	if (NULL != filter) {
		ParseXMLSettingsFilter(filter);
	}

	tinyxml2::XMLElement* view = docHandle.FirstChildElement("view").ToElement();
	while (NULL != view) {
		ParseXMLSettingsView(view);
		view = view->NextSiblingElement("view");
	}
}

template<typename PARSER>
Level<PARSER>::Level(t_bool_parser boolParser
		, t_long_parser longParser
		, t_string_parser stringParser
)
	: BoolLogicParser(boolParser)
	, LongLogicParser(longParser)
	, StringLogicParser(stringParser)
{
}

template class Level<ParserEtherNet>;
template class Level<ParserEtherNetDIX>;
template class Level<ParserEtherNetSNAP>;
template class Level<ParserEtherNetRAW>;
template class Level<ParserEtherNet802LLC>;

template class Level<ParserIPv4>;
template class Level<ParserIPv6>;
template class Level<ParserTCP>;
template class Level<ParserUDP>;
template class Level<ParserPacketIPv4>;
template class Level<ParserSessionTCP>;

} /* namespace level */
} /* namespace ttop */
