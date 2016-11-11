
#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <memory>
#include <climits>
#include <iostream>
#include "../Logic.h"
#include <exception>

namespace ttop {
namespace view {

template <typename INCHUNK>
class Value {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) = 0;
	virtual std::string OutputString() = 0;
	virtual unsigned long long OutputLongLong() = 0;

	virtual ~Value() {}
};

/*
template <typename INCHUNK>
class ValueLongLong : public Value<INCHUNK> {
public:
	typedef logic::Logic<INCHUNK, unsigned bool> t_input;

	std::unique_ptr<t_input> Logic;
	unsigned long long Current = 0;

	virtual std::string OutputString() {
		return (std::to_string(Current));
	}

	virtual unsigned long long OutputLongLong() {
		return (Current);
	}

	ValueLongLong(tinyxml2::XMLElement *node
			, logic::Logic<INCHUNK, bool> boolLogic) {
		Logic = boolLogic.Clone();
		Logic->Algorithm = Logic->Parse(node);
	}

	virtual ~ValueLongLong() {}
};

template <typename INCHUNK>
class ValueMax : public ValueLongLong<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		unsigned long long v = this->Logic->Evaluate(chunk);
		this->Current = std::max(this->Current, v);
	}

	ValueMax(tinyxml2::XMLElement *node
			, logic::Logic<INCHUNK, bool> boolLogic)
		: ValueLongLong<INCHUNK>(node, boolLogic) {}

	virtual ~ValueMax() {}
};
*/

template <typename INCHUNK>
class ValueBool : public Value<INCHUNK> {
public:
	typedef logic::Logic<INCHUNK, bool> t_logic;
	typedef std::function<bool(std::shared_ptr<INCHUNK>)> t_algorithm;

	t_algorithm Algorithm;

	virtual std::string OutputString() {
		// TODO
		return ("123456");
	}

	virtual unsigned long long OutputLongLong() {
		// TODO
		return (123456);
	}

	ValueBool(tinyxml2::XMLElement *node
			, std::shared_ptr<t_logic> boolLogic) {
		tinyxml2::XMLElement *logic = node->FirstChild()->ToElement();
		if (logic != NULL) {
			Algorithm = boolLogic->ParseBool(logic);
		} else {
			throw logic::ParseError("bool value expected");
		}
	}

	virtual ~ValueBool() {}
};

template <typename INCHUNK>
class ValueTestBool : public ValueBool<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		bool v = this->Algorithm(chunk);
	}

	ValueTestBool(tinyxml2::XMLElement *node
			, std::shared_ptr<logic::Logic<INCHUNK, bool> > boolLogic)
		: ValueBool<INCHUNK>(node, boolLogic) {}

	virtual ~ValueTestBool() {}
};



template <typename IN>
class View {
	std::shared_ptr<logic::Logic<IN, bool> > BoolParser;
	std::shared_ptr<Value<IN> > test;
public:
	virtual std::string TypeID() = 0;

	void Input(std::shared_ptr<IN> chunk)
	{
		test->Input(chunk);
		std::string r = test->OutputString();

		std::cout << "Line: " << r << "\n";
	}

	virtual void ParseParams(tinyxml2::XMLElement *node) {};

	std::shared_ptr<Value<IN> > ParseSelect(tinyxml2::XMLElement *node) {
		tinyxml2::XMLElement *logic = node->FirstChild()->ToElement();
		if (logic != NULL) {
			std::string name(logic->Value());
			if (name == "testbool") {
				std::shared_ptr<ValueTestBool<IN> > r
					= std::make_shared<ValueTestBool<IN> >(logic, BoolParser);
				return (r);
			}
			throw logic::ParseError("unknown selection type");
		}
		throw logic::ParseError("<select/> must have a child");
	}

	void ParseSelects(tinyxml2::XMLElement *node) {
		tinyxml2::XMLHandle docHandle(node);
		tinyxml2::XMLElement* select = docHandle.FirstChildElement("select").ToElement();
		while (NULL != select) {
			test = ParseSelect(select);
			select = select->NextSiblingElement("select");
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

	View(std::shared_ptr<logic::Logic<IN, bool> > boolParser)
		: BoolParser(boolParser)
	{
	}

	virtual ~View() {}
};

} /* namespace view */
} /* namespace ttop */

#endif /* SRC_VIEW_VIEW_H_ */
