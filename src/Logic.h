
#ifndef SRC_LOGIC_H_
#define SRC_LOGIC_H_

#include <functional>
#include <exception>
#include <memory>
#include "tinyxml2.h"
#include <ctime>

namespace ttop {
namespace logic {

class ParseError: public std::runtime_error
{
public:
	ParseError(const std::string &msg) : std::runtime_error(msg) {};
};

template <typename IN>
class Logic {
public:
	typedef std::shared_ptr<IN> t_input;

	typedef std::function<std::string(t_input)> t_string_value;
	typedef std::function<long long(t_input)> t_longlong_value;
	typedef std::function<bool(t_input)> t_bool_value;

	t_bool_value True = [](t_input) { return (true); };
	t_bool_value False = [](t_input) { return (false); };

	virtual ~Logic();

	t_bool_value ToBoolValue(t_bool_value &v);
	t_bool_value ToBoolValue(t_string_value &v);
	t_bool_value ToBoolValue(t_longlong_value &v);

	virtual t_string_value ParseStringCustom (tinyxml2::XMLElement &elt);

	t_string_value ParseString(tinyxml2::XMLElement *elt);

	virtual t_longlong_value ParseLongLongCustom (tinyxml2::XMLElement &elt);

	t_longlong_value ParseLongLong(tinyxml2::XMLElement *elt);
	virtual t_bool_value ParseBoolCustom (tinyxml2::XMLElement &elt);
	t_bool_value ParseBool(tinyxml2::XMLElement *elt);
};

} /* namespace logic */
} /* namespace ttop */

#endif /* SRC_LOGIC_H_ */
