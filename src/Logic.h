
#ifndef SRC_LOGIC_H_
#define SRC_LOGIC_H_

#include <functional>
#include <exception>
#include <memory>
#include "tinyxml2.h"

namespace ttop {
namespace logic {

class ParseError: public std::runtime_error
{
public:
	ParseError(const std::string &msg) : std::runtime_error(msg) {};
};

template <typename IN, typename OUT>
class Logic {
public:
	typedef std::function<OUT(std::shared_ptr<IN>)> t_logic;

	t_logic Algorithm;

	typedef std::function<std::string(std::shared_ptr<IN>)> t_string_value;
	typedef std::function<long long(std::shared_ptr<IN>)> t_longlong_value;
	typedef std::function<bool(std::shared_ptr<IN>)> t_bool_value;
	typedef std::function<bool(t_string_value, t_string_value, std::shared_ptr<IN>)> t_string_operator;
	typedef std::function<bool(t_longlong_value, t_longlong_value, std::shared_ptr<IN>)> t_longlong_operator;

	typedef std::function<bool(t_bool_value, t_bool_value, std::shared_ptr<IN>)> t_bool_operator;

	t_bool_operator BoolAnd = [](t_bool_value a, t_bool_value b, std::shared_ptr<IN> v) { return(a(v) && b(v)); };
	t_bool_operator BoolOr = [](t_bool_value a, t_bool_value b, std::shared_ptr<IN> v) { return(a(v) || b(v)); };
	t_string_operator StringEquals = [](t_string_value a, t_string_value b, std::shared_ptr<IN> v) { return(a(v) == b(v)); };
	t_longlong_operator LongLongEquals = [](t_longlong_value a, t_longlong_value b, std::shared_ptr<IN> v) { return(a(v) == b(v)); };

	t_bool_value True = [](std::shared_ptr<IN>) { return (true); };
	t_bool_value False = [](std::shared_ptr<IN>) { return (false); };

	t_string_value String(const std::string &v) { return([v](std::shared_ptr<IN>) { return (v); }); };
	t_longlong_value LongLong(long long int &v) { return([v](std::shared_ptr<IN>) { return (v); }); };

	virtual OUT Evaluate(std::shared_ptr<IN> input) {
		return (Algorithm(input));
	}

	virtual ~Logic() {}

	t_bool_value ToBoolValue(t_bool_value &v) { return (v); };
	t_bool_value ToBoolValue(t_string_value &v) { return (True); };
	t_bool_value ToBoolValue(t_longlong_value &v) { return (True); };

	virtual t_string_value ParseStringCustom (tinyxml2::XMLElement &elt) {
		throw ParseError((std::string)"Logic parser got unexpected XML node where string value expected: " + elt.Value());
	}

	t_string_value ParseString(tinyxml2::XMLElement *elt) {
		if (elt) {
			std::string name(elt->Value());

			if (name == "string") {
				std::string value(elt->GetText());
				return (String(value));
			}
			return (ParseStringCustom(*elt));
		}
		throw ParseError("Logic parser found no XML child");
	}

	virtual t_longlong_value ParseLongLongCustom (tinyxml2::XMLElement &elt) {
		throw ParseError((std::string)"Logic parser got unexpected XML node where long value expected: " + elt.Value());
	}

	t_longlong_value ParseLongLong(tinyxml2::XMLElement *elt) {
		if (elt) {
			std::string name(elt->Value());

			if (name == "long") {
				std::string value(elt->GetText());
				long long v = std::stoll(value);
				t_longlong_value r = LongLong(v);
				return (r);
			}
			return (ParseLongLongCustom(*elt));
		}
		throw ParseError("Logic parser found no XML child");
	}

	virtual t_bool_value ParseBoolCustom (tinyxml2::XMLElement &elt) {
		throw ParseError((std::string)"Logic parser got unexpected XML node where bool value expected: " + elt.Value());
	}

	t_bool_value ParseBool(tinyxml2::XMLElement *elt) {
		if (elt) {
			std::string name(elt->Value());

			if (name == "true") {
				return (True);

			} else if (name == "false") {
				return (False);

			} else if (name == "or") {
				tinyxml2::XMLElement *first = elt->FirstChild()->ToElement();
				if (first) {
					tinyxml2::XMLElement *second = first->NextSibling()->ToElement();
					if (second) {
						t_bool_value s_first = ParseBool(first);
						t_bool_value s_second = ParseBool(second);
						t_bool_value r = std::bind(BoolOr, s_first, s_second, std::placeholders::_1);
						return (r);
					}
					throw ParseError("Logic parser found no second node for node '" + name + "'");
				}
				throw ParseError("Logic parser found no children for node '" + name + "'");

			} else if (name == "stringEq" || name == "longEq") {
				tinyxml2::XMLElement *first = elt->FirstChild()->ToElement();
				if (first) {
					tinyxml2::XMLElement *second = first->NextSibling()->ToElement();
					if (second) {
						if (name == "stringEq") {
							t_string_value s_first = ParseString(first);
							t_string_value s_second = ParseString(second);
							t_bool_value r = std::bind(StringEquals, s_first, s_second, std::placeholders::_1);
							return (r);
						} else {
							t_longlong_value s_first = ParseLongLong(first);
							t_longlong_value s_second = ParseLongLong(second);
							t_bool_value r = std::bind(LongLongEquals, s_first, s_second, std::placeholders::_1);
							return (r);
						}
					}
					throw ParseError("Logic parser found no second node for node '" + name + "'");
				}
				throw ParseError("Logic parser found no children for node '" + name + "'");
			}
			return (ParseBoolCustom(*elt));
		}
		throw ParseError("Logic parser found no XML child");
	}
};

} /* namespace logic */
} /* namespace ttop */

#endif /* SRC_LOGIC_H_ */
