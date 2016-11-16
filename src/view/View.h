
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

template <typename IN>
struct Selection {
	typedef std::function<std::string(std::shared_ptr<IN>)> t_logic;
	std::string Name;
	t_logic SavedLogic;
	t_logic Logic;
	std::string Value;

	void Input(std::shared_ptr<IN> chunk) {
		Value = Logic(chunk);
	}

	void Reset() {
		Logic = SavedLogic;
		Value = "";
	}

	Selection(std::string name, t_logic logic) : Name(name), SavedLogic(logic), Logic(logic) {};
};

template <typename IN>
class View {
	std::shared_ptr<logic::Logic<IN, bool> > BoolParser;
	std::shared_ptr<logic::Logic<IN, unsigned long long> > LongParser;
	std::shared_ptr<logic::Logic<IN, std::string> > StringParser;
public:
	std::vector< std::shared_ptr<Selection<IN> > > Selection_list;
	virtual std::string TypeID() = 0;
	virtual void Output() {};

	void Input(std::shared_ptr<IN> chunk)
	{
		for (auto s : Selection_list) {
			s->Input(chunk);
		}

		// TODO
		if (true) {
			Output();
			for (auto s : Selection_list) {
//				s->Reset();
			}
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
				std::shared_ptr< Selection<IN> > s = std::make_shared< Selection<IN> >(name, v);
				Selection_list.push_back(s);
				child = child->NextSibling();
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
