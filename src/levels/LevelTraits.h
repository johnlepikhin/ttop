
#ifndef SRC_LEVELS_LEVELTRAITS_H_
#define SRC_LEVELS_LEVELTRAITS_H_

#include "../ParserDescription.h"
#include "../Filter.h"
#include <memory>
#include <exception>

namespace ttop {
namespace level {

template <typename PARSER>
class LevelTraits : public PARSER {
public:
	typedef ttop::logic::Filter<typename PARSER::THIS_T> t_filter;
	typedef std::shared_ptr<typename PARSER::THIS_T> t_value;

	std::unique_ptr<t_filter> FilterLogic = std::unique_ptr<t_filter>(new t_filter());

	virtual ~LevelTraits() {};

	virtual struct parserDescription::Description GetDescription() = 0;
	virtual bool Filter(t_value chunk);
	virtual bool BeforeRecursionHook(t_value chunk);

	void ParseXMLSettings(tinyxml2::XMLElement *node);
	void ParseXMLSettingsFilter(tinyxml2::XMLElement *node);
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_LEVELTRAITS_H_ */
