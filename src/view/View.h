
#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <memory>
#include <climits>
#include <iostream>
#include "../Logic.h"
#include <exception>
#include <vector>
#include <unordered_map>

namespace ttop {
namespace view {

template <typename IN, typename VALUE>
struct Value {
	typedef std::function<VALUE(std::shared_ptr<IN>)> t_logic;
	std::string Name;
	t_logic SavedLogic;
	t_logic Logic;
	VALUE Val;

	void Input(std::shared_ptr<IN> chunk) {
		Val = Logic(chunk);
	}

	void Reset() {
		Logic = SavedLogic;
	}

	Value(t_logic logic) : SavedLogic(logic), Logic(logic) {};
	Value(std::string name, t_logic logic) : Name(name), SavedLogic(logic), Logic(logic) {};
};

template <typename IN>
class View {
	std::shared_ptr<logic::Logic<IN, bool> > BoolParser;
	std::shared_ptr<logic::Logic<IN, unsigned long long> > LongParser;
	std::shared_ptr<logic::Logic<IN, std::string> > StringParser;
	std::function<bool(std::shared_ptr<IN>)> True = [](std::shared_ptr<IN>) { return (true); };
	std::function<std::string(std::shared_ptr<IN>)> EmptyString = [](std::shared_ptr<IN>) { return (""); };
public:
	typedef Value<IN, std::string> t_select;
	typedef std::vector< t_select > t_selection;
	t_selection Selection_source;
	std::unordered_map<std::string, t_selection> Selection;
	Value<IN, bool> Where = Value<IN, bool>(True);
	Value<IN, bool> Trigger = Value<IN, bool>(True);
	Value<IN, typename std::string> GroupBy = Value<IN, typename std::string>(EmptyString);
	virtual std::string TypeID() = 0;
	virtual void Output() {};

	void FillSelection(t_selection &vector, std::shared_ptr<IN> chunk) {
		for (auto it = vector.begin(); it!=vector.end(); ++it) {
			(*it).Input(chunk);
		}
	}

	void Input(std::shared_ptr<IN> chunk)
	{
		Where.Input(chunk);
		Trigger.Input(chunk);

		if (Where.Val) {
			GroupBy.Input(chunk);
			auto g = Selection.find(GroupBy.Val);
			if (g == Selection.end()) {
				t_selection vector = Selection_source;
				FillSelection(vector, chunk);
				Selection.emplace(GroupBy.Val, vector);
			} else {
				FillSelection(g->second, chunk);
			}
		}

		if (Trigger.Val) {
			Output();
//			for (auto it = Selection_source.begin(); it!=Selection_source.end(); ++it) {
//				(*it).Reset();
//			}
			Where.Reset();
			Trigger.Reset();
			GroupBy.Reset();
			Selection.clear();
		}
	}

	virtual void ParseParams(tinyxml2::XMLElement *node) {};

	void ParseSelects(tinyxml2::XMLElement *node) {
		tinyxml2::XMLHandle docHandle(node);
		tinyxml2::XMLElement* select = docHandle.FirstChildElement("select").ToElement();
		if (select) {
			tinyxml2::XMLNode *child = select->FirstChild();
			while (child) {
				tinyxml2::XMLElement *elt = child->ToElement();
				if (elt) {
					const char *_name = elt->Attribute("name");
					std::string name = (_name) ? _name : "";
					std::function<std::string(std::shared_ptr<IN>)> v = StringParser->ParseString(elt);
					Value<IN, std::string>  s(name, v);
					Selection_source.push_back(s);
				}
				child = child->NextSibling();
			}
		}
	}

	void ParseWhere(tinyxml2::XMLElement *node) {
		if (tinyxml2::XMLNode *child = node->FirstChildElement("where")) {
			child = child->FirstChildElement();
			if (child) {
				tinyxml2::XMLElement *elt = child->ToElement();
				if (elt) {
					Where = BoolParser->ParseBool(elt);
					return;
				}
			}
			throw logic::ParseError("Bool child node required for <where/>");
		}
	}

	void ParseTrigger(tinyxml2::XMLElement *node) {
		if (tinyxml2::XMLNode *child = node->FirstChildElement("trigger")) {
			child = child->FirstChildElement();
			if (child) {
				tinyxml2::XMLElement *elt = child->ToElement();
				if (elt) {
					Trigger = BoolParser->ParseBool(elt);
					return;
				}
			}
			throw logic::ParseError("Bool child node required for <trigger/>");
		}
	}

	void ParseGroupBy(tinyxml2::XMLElement *node) {
		if (tinyxml2::XMLNode *child = node->FirstChildElement("groupBy")) {
			child = child->FirstChildElement();
			if (child) {
				tinyxml2::XMLElement *elt = child->ToElement();
				if (elt) {
					GroupBy = StringParser->ParseString(elt);
					return;
				}
			}
			throw logic::ParseError("Bool child node required for <groupBy/>");
		}
	}

	void Parse(tinyxml2::XMLElement *node, std::string &type)
	{
		const char *_type = node->Attribute("type");
		if (_type) {
			if (TypeID() == _type) {
				ParseParams(node);
				ParseSelects(node);
				ParseWhere(node);
				ParseTrigger(node);
				ParseGroupBy(node);
			} else {
				throw std::invalid_argument("unknown view type");
			}
		} else {
			throw logic::ParseError("type= is required for <view/>");
		}
	}

	View(std::shared_ptr<logic::Logic<IN, bool> > boolParser
			, std::shared_ptr<logic::Logic<IN, unsigned long long> > longParser
			, std::shared_ptr<logic::Logic<IN, std::string> > stringParser
			)
		: BoolParser(boolParser)
		, LongParser(longParser)
		, StringParser(stringParser)
	{
	}

	virtual ~View() {}
};

} /* namespace view */
} /* namespace ttop */

#endif /* SRC_VIEW_VIEW_H_ */
