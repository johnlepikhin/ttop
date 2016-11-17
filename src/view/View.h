
#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <memory>
#include <climits>
#include <iostream>
#include "../Logic.h"
#include <exception>
#include <vector>

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
public:
	std::vector< std::shared_ptr<Value<IN, std::string> > > Selection_list;
	Value<IN, bool> Where = Value<IN, bool>(True);
	Value<IN, bool> Trigger = Value<IN, bool>(True);
	virtual std::string TypeID() = 0;
	virtual void Output() {};

	void Input(std::shared_ptr<IN> chunk)
	{
		Where.Input(chunk);
		Trigger.Input(chunk);

		if (Where.Val) {
			for (auto s : Selection_list) {
				s->Input(chunk);
			}
		}

		if (Trigger.Val) {
			Output();
			for (auto s : Selection_list) {
				s->Reset();
			}
			Where.Reset();
			Trigger.Reset();
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
				const char *_name = elt->Attribute("name");
				std::string name = (_name) ? _name : "";
				std::function<std::string(std::shared_ptr<IN>)> v = StringParser->ParseString(elt);
				std::shared_ptr< Value<IN, std::string> > s
					= std::make_shared< Value<IN, std::string> >(name, v);
				Selection_list.push_back(s);
				child = child->NextSibling();
			}
		}
	}

	void ParseWhere(tinyxml2::XMLElement *node) {
		if (tinyxml2::XMLNode *child = node->FirstChildElement("where")) {
			child = child->FirstChildElement();
			if (child) {
				tinyxml2::XMLElement *elt = child->ToElement();
				Where = BoolParser->ParseBool(elt);
			}
		}
	}

	void ParseTrigger(tinyxml2::XMLElement *node) {
		if (tinyxml2::XMLNode *child = node->FirstChildElement("trigger")) {
			child = child->FirstChildElement();
			if (child) {
				tinyxml2::XMLElement *elt = child->ToElement();
				Trigger = BoolParser->ParseBool(elt);
			}
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
