
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

	Value(t_logic logic, VALUE initialValue)
		: SavedLogic(logic)
		, Logic(logic)
		, Val(initialValue) {};
	Value(std::string name, t_logic logic, VALUE initialValue)
		: Name(name)
		, SavedLogic(logic)
		, Logic(logic)
		, Val(initialValue) {};
};

template <typename IN>
class View {
	std::shared_ptr<logic::Logic<IN> > Parser;
	std::function<bool(std::shared_ptr<IN>)> True = [](std::shared_ptr<IN>) { return (true); };
	std::function<std::string(std::shared_ptr<IN>)> EmptyString = [](std::shared_ptr<IN>) { return (""); };
public:
	typedef Value<IN, std::string> t_select;
	typedef std::vector< t_select > t_selection;
	t_selection Selection_source;
	std::unordered_map<std::string, t_selection> Selection;
	Value<IN, bool> Where = Value<IN, bool>(True, true);
	Value<IN, bool> Trigger = Value<IN, bool>(True, true);
	Value<IN, typename std::string> GroupBy = Value<IN, typename std::string>(EmptyString, "");
	virtual std::string TypeID() = 0;
	virtual void Output();

	void FillSelection(t_selection &vector, std::shared_ptr<IN> chunk);
	void Input(std::shared_ptr<IN> chunk);
	virtual void ParseParams(tinyxml2::XMLElement *node);

	void ParseSelects(tinyxml2::XMLElement *node);
	void ParseWhere(tinyxml2::XMLElement *node);
	void ParseTrigger(tinyxml2::XMLElement *node);
	void ParseGroupBy(tinyxml2::XMLElement *node);
	void Parse(tinyxml2::XMLElement *node, std::string &type);
	View(std::shared_ptr<logic::Logic<IN> > parser);
	virtual ~View();
};

} /* namespace view */
} /* namespace ttop */

#endif /* SRC_VIEW_VIEW_H_ */
