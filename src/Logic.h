
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

	typedef std::function<std::string(const t_input &)> t_string_value;
	typedef std::function<long long(const t_input &)> t_longlong_value;
	typedef std::function<bool(const t_input &)> t_bool_value;

	t_bool_value True = [](const t_input &) { return (true); };
	t_bool_value False = [](const t_input &) { return (false); };

	virtual ~Logic();

	t_bool_value ToBoolValue(const t_bool_value &v);
	t_bool_value ToBoolValue(const t_string_value &v);
	t_bool_value ToBoolValue(const t_longlong_value &v);

	virtual t_string_value ParseStringCustom (const tinyxml2::XMLElement &elt);

	t_string_value ParseString(const tinyxml2::XMLElement *elt);

	virtual t_longlong_value ParseLongLongCustom (const tinyxml2::XMLElement &elt);

	t_longlong_value ParseLongLong(const tinyxml2::XMLElement *elt);
	virtual t_bool_value ParseBoolCustom (const tinyxml2::XMLElement &elt);
	t_bool_value ParseBool(const tinyxml2::XMLElement *elt);
};

} /* namespace logic */
} /* namespace ttop */

#endif /* SRC_LOGIC_H_ */
