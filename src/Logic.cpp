// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Logic.h"
#include "ParserDescription.h"

namespace ttop {
namespace logic {


template <typename IN>
Logic<IN>::~Logic() {}

template <typename IN>
typename Logic<IN>::t_bool_value Logic<IN>::ToBoolValue(const t_bool_value &v) { return (v); };

template <typename IN>
typename Logic<IN>::t_bool_value Logic<IN>::ToBoolValue(const t_string_value &v) { return (True); };

template <typename IN>
typename Logic<IN>::t_bool_value Logic<IN>::ToBoolValue(const t_longlong_value &v) { return (True); };

template <typename IN>
typename Logic<IN>::t_string_value Logic<IN>::ParseStringCustom (const tinyxml2::XMLElement &elt) {
	throw ParseError(std::string("Logic parser got unexpected XML node where string value expected: ") + elt.Value());
}

template <typename IN>
typename Logic<IN>::t_string_value Logic<IN>::ParseString(const tinyxml2::XMLElement *elt) {
	if (elt) {
		std::string name(elt->Value());

		if (name == "string") {
			std::string v = elt->GetText();
			return([v](const t_input &) { return (v); });
		} else if (name == "long2string") {
			if (const tinyxml2::XMLElement *first = elt->FirstChild()->ToElement()) {
				t_longlong_value s_first = ParseLongLong(first);
				return ([s_first](const t_input &v) { return(std::to_string(s_first(v))); });
			}
			throw ParseError("Logic parser found no children for node '" + name + "'");
		}
		return (ParseStringCustom(*elt));
	}
	throw ParseError("Logic parser found no XML child");
}

template <typename IN>
typename Logic<IN>::t_longlong_value Logic<IN>::ParseLongLongCustom (const tinyxml2::XMLElement &elt) {
	throw ParseError(static_cast<std::string>("Logic parser got unexpected XML node where long value expected: ") + elt.Value());
}

template <typename IN>
typename Logic<IN>::t_longlong_value Logic<IN>::ParseLongLong(const tinyxml2::XMLElement *elt) {
	if (elt) {
		std::string name(elt->Value());

		if (name == "long") {
			std::string value(elt->GetText());
			long long v = std::stoll(value);
			return([v](t_input) { return (v); });
		} else if (name == "max" || name == "min" || name == "sum" || name == "avg") {
			const tinyxml2::XMLNode *_first = elt->FirstChild();
			const tinyxml2::XMLElement *first;
			if (_first && (first = _first->ToElement())) {
				t_longlong_value s_first = ParseLongLong(first);
				long long current = 0;
				if (name == "max") {
					return ([current, s_first](const t_input &v) mutable {
						current = std::max(current, s_first(v));
						return(current);
					});
				} else if (name == "min") {
					current = LLONG_MAX;
					return ([current, s_first](const t_input &v) mutable {
						current = std::min(current, s_first(v));
						return(current);
					});
				} else if (name == "sum") {
					return ([current, s_first](const t_input &v) mutable {
						current += s_first(v);
						return(current);
					});
				} else if (name == "avg") {
					long long count = 0;
					return ([current, count, s_first](const t_input &v) mutable {
						current += s_first(v);
						count ++;
						return(current/count);
					});
				}
			}
			throw ParseError("Logic parser found no children for node '" + name + "'");
		} else if (name == "plus"
				|| name == "minus"
				|| name == "mul"
				|| name == "div") {
			const tinyxml2::XMLNode *node = elt->FirstChild();
			const tinyxml2::XMLElement *first, *second;
			if (node && (first = node->ToElement())) {
				node = node->NextSiblingElement();
				if (node && (second = node->ToElement())) {
					t_longlong_value s_first = ParseLongLong(first);
					t_longlong_value s_second = ParseLongLong(second);
					if (name == "plus") {
						return ([s_first, s_second](const t_input &v) mutable {
							return(s_first(v) + s_second(v));
						});
					} else if (name == "minus") {
						return ([s_first, s_second](const t_input &v) mutable {
							return(s_first(v) - s_second(v));
						});
					} else if (name == "mul") {
						return ([s_first, s_second](const t_input &v) mutable {
							return(s_first(v) * s_second(v));
						});
					} else if (name == "div") {
						return ([s_first, s_second](const t_input &v) mutable {
							return(s_first(v) / s_second(v));
						});
					}
				}
				throw ParseError("Logic parser found no second child for node '" + name + "'");
			}
			throw ParseError("Logic parser found no children for node '" + name + "'");
		} else if (name == "nowSeconds") {
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

template <typename IN>
typename Logic<IN>::t_bool_value Logic<IN>::ParseBoolCustom (const tinyxml2::XMLElement &elt) {
	throw ParseError(static_cast<std::string>("Logic parser got unexpected XML node where bool value expected: ") + elt.Value());
}

template <typename IN>
typename Logic<IN>::t_bool_value Logic<IN>::ParseBool(const tinyxml2::XMLElement *elt) {
	if (elt) {
		std::string name(elt->Value());

		if (name == "true") {
			return (True);

		} else if (name == "false") {
			return (False);

		} else if (name == "or" || name == "and") {
			const tinyxml2::XMLElement *first = elt->FirstChild()->ToElement();
			if (first) {
				const tinyxml2::XMLElement *second = first->NextSibling()->ToElement();
				if (second) {
					t_bool_value s_first = ParseBool(first);
					t_bool_value s_second = ParseBool(second);
					if (name == "or") {
						return ([s_first, s_second](const t_input &v) { return(s_first(v) || s_second(v)); });
					} else if (name == "and") {
						return ([s_first, s_second](const t_input &v) { return(s_first(v) && s_second(v)); });
					}
				}
				throw ParseError("Logic parser found no second node for node '" + name + "'");
			}
			throw ParseError("Logic parser found no children for node '" + name + "'");

		} else if (name == "not") {
			const tinyxml2::XMLElement *first = elt->FirstChild()->ToElement();
			if (first) {
				t_bool_value s_first = ParseBool(first);
				return ([s_first](const t_input &v) { return(not(s_first(v))); });
			}
			throw ParseError("Logic parser found no children for node '" + name + "'");

		} else if (name == "longGt"
				|| name == "longLt"
				|| name == "longGtEq"
				|| name == "longLtEq") {
			const tinyxml2::XMLNode *node = elt->FirstChild();
			const tinyxml2::XMLElement *first, *second;
			if (node && (first = node->ToElement())) {
				node = node->NextSiblingElement();
				if (node && (second = node->ToElement())) {
					t_longlong_value s_first = ParseLongLong(first);
					t_longlong_value s_second = ParseLongLong(second);
					if (name == "longGt") {
						return ([s_first, s_second](const t_input &v) mutable {
							return(s_first(v) > s_second(v));
						});
					} else if (name == "longLt") {
						return ([s_first, s_second](const t_input &v) mutable {
							return(s_first(v) < s_second(v));
						});
					} else if (name == "longGtEq") {
						return ([s_first, s_second](const t_input &v) mutable {
							return(s_first(v) >= s_second(v));
						});
					} else if (name == "longLtEq") {
						return ([s_first, s_second](const t_input &v) mutable {
							return(s_first(v) <= s_second(v));
						});
					}
				}
				throw ParseError("Logic parser found no second child for node '" + name + "'");
			}
			throw ParseError("Logic parser found no children for node '" + name + "'");


		} else if (name == "stringEq" || name == "longEq") {
			const tinyxml2::XMLElement *first = elt->FirstChild()->ToElement();
			if (first) {
				const tinyxml2::XMLElement *second = first->NextSibling()->ToElement();
				if (second) {
					if (name == "stringEq") {
						t_string_value s_first = ParseString(first);
						t_string_value s_second = ParseString(second);
						return ([s_first, s_second](const t_input &v){return (s_first(v) == s_second(v)); });
					} else {
						t_longlong_value s_first = ParseLongLong(first);
						t_longlong_value s_second = ParseLongLong(second);
						return ([s_first, s_second](const t_input &v){return (s_first(v) == s_second(v)); });
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


template class Logic<ChunkEtherNet>;
template class Logic<ChunkEtherNetDIX>;
template class Logic<ChunkEtherNetSNAP>;
template class Logic<ChunkEtherNetRAW>;
template class Logic<ChunkEtherNet802LLC>;

template class Logic<ChunkIPv4>;
template class Logic<ChunkIPv6>;
template class Logic<ChunkTCP>;
template class Logic<ChunkUDP>;
template class Logic<PacketIPv4>;
template class Logic<PacketIPVariant>;
template class Logic<SessionTCP>;
template class Logic<EndPoint>;
template class Logic<ChunkHTTP>;
template class Logic<PacketMySQL>;

} /* namespace logic */
} /* namespace ttop */
