
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

template <typename IN, typename OUT>
class Logic {
public:
	typedef std::shared_ptr<IN> t_input;
	typedef std::function<OUT(t_input)> t_logic;

	OUT DefaultValue;

	typedef std::function<std::string(t_input)> t_string_value;
	typedef std::function<long long(t_input)> t_longlong_value;
	typedef std::function<bool(t_input)> t_bool_value;

	t_bool_value True = [](t_input) { return (true); };
	t_bool_value False = [](t_input) { return (false); };

	Logic (OUT defaultValue)
	{
		DefaultValue = defaultValue;
	}

	t_logic GetDefault() {
		return ([this](t_input) { return (this->DefaultValue); });
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
				std::string v = elt->GetText();
				return([v](t_input) { return (v); });
			} else if (name == "long2string") {
				if (tinyxml2::XMLElement *first = elt->FirstChild()->ToElement()) {
					t_longlong_value s_first = ParseLongLong(first);
					return ([s_first](t_input v) { return(std::to_string(s_first(v))); });
				}
				throw ParseError("Logic parser found no children for node '" + name + "'");
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
				return([v](t_input) { return (v); });
			} else if (name == "max" || name == "min" || name == "sum" || name == "avg") {
				if (tinyxml2::XMLElement *first = elt->FirstChild()->ToElement()) {
					t_longlong_value s_first = ParseLongLong(first);
					long long current = 0;
					if (name == "max") {
						return ([current, s_first](t_input v) mutable {
							current = std::max(current, s_first(v));
							return(current);
						});
					} else if (name == "min") {
						long long current = LLONG_MAX;
						return ([current, s_first](t_input v) mutable {
							current = std::min(current, s_first(v));
							return(current);
						});
					} else if (name == "sum") {
						return ([current, s_first](t_input v) mutable {
							current += s_first(v);
							return(current);
						});
					} else if (name == "avg") {
						long long count = 0;
						return ([current, count, s_first](t_input v) mutable {
							current += s_first(v);
							count ++;
							return(current/count);
						});
					}
				}
				throw ParseError("Logic parser found no children for node '" + name + "'");
			} else if (name == "now_seconds") {
				return ([](t_input v) mutable {
					return(std::time(nullptr));
				});
			} else if (name == "counter") {
				long long current = 0;
				return ([current](t_input v) mutable {
					current++;
					return(current);
				});
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

			} else if (name == "or" || name == "and") {
				tinyxml2::XMLElement *first = elt->FirstChild()->ToElement();
				if (first) {
					tinyxml2::XMLElement *second = first->NextSibling()->ToElement();
					if (second) {
						t_bool_value s_first = ParseBool(first);
						t_bool_value s_second = ParseBool(second);
						if (name == "or") {
							return ([s_first, s_second](t_input v) { return(s_first(v) || s_second(v)); });
						} else if (name == "and") {
							return ([s_first, s_second](t_input v) { return(s_first(v) && s_second(v)); });
						}
					}
					throw ParseError("Logic parser found no second node for node '" + name + "'");
				}
				throw ParseError("Logic parser found no children for node '" + name + "'");

			} else if (name == "not") {
				tinyxml2::XMLElement *first = elt->FirstChild()->ToElement();
				if (first) {
					t_bool_value s_first = ParseBool(first);
					return ([s_first](t_input v) { return(not(s_first(v))); });
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
							return ([s_first, s_second](t_input v){return (s_first(v) == s_second(v)); });
						} else {
							t_longlong_value s_first = ParseLongLong(first);
							t_longlong_value s_second = ParseLongLong(second);
							return ([s_first, s_second](t_input v){return (s_first(v) == s_second(v)); });
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
