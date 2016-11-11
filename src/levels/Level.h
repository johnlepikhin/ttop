
#ifndef SRC_LEVELS_LEVEL_H_
#define SRC_LEVELS_LEVEL_H_

#include "../ParserDescription.h"
#include "../Logic.h"
#include "../view/Dump.h"
#include <memory>
#include <exception>

namespace ttop {
namespace level {

template <typename PARSER>
class Level : public PARSER {
public:
	typedef typename PARSER::THIS_T THIS_T;

	typedef std::function<bool(std::shared_ptr<THIS_T>)> t_bool;
	typedef std::shared_ptr<logic::Logic<THIS_T, bool> > t_bool_parser;

	typedef logic::Logic<THIS_T, bool> t_string;
	typedef logic::Logic<THIS_T, bool> t_longlong;

	typedef view::View<THIS_T> t_view;
	typedef std::shared_ptr<THIS_T> t_value;

	t_bool_parser BoolLogicParser = t_bool_parser(true);
	t_bool FilterAlgorithm = BoolLogicParser->True;

	std::vector<std::shared_ptr<t_view > > Views;

	Level(t_bool_parser boolParser);
	virtual ~Level() {};

	virtual struct parserDescription::Description GetDescription() = 0;
	virtual bool Filter(t_value chunk);
	virtual bool BeforeRecursionHook(t_value chunk);

	void ParseXMLSettings(tinyxml2::XMLElement *node);
	void ParseXMLSettingsFilter(tinyxml2::XMLElement *node);
	void ParseXMLSettingsView(tinyxml2::XMLElement *node);
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_LEVEL_H_ */
