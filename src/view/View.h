
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

template <typename INCHUNK>
class Value {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) = 0;
	virtual std::string OutputString() = 0;
	virtual unsigned long long OutputLongLong() = 0;

	virtual ~Value() {}
};

template <typename INCHUNK>
class ValueLong : public Value<INCHUNK> {
public:
	typedef logic::Logic<INCHUNK, unsigned long long> t_logic;
	typedef std::function<unsigned long long(std::shared_ptr<INCHUNK>)> t_algorithm;
	unsigned long long Value = 0;

	t_algorithm Algorithm;

	virtual std::string OutputString() {
		return (std::to_string(Get()));
	}

	virtual unsigned long long OutputLongLong() {
		return (Get());
	}

	virtual unsigned long long Get() {
		return (Value);
	}

	ValueLong(tinyxml2::XMLElement *node
			, std::shared_ptr<t_logic> algorithm
			, bool logicRequired) {
		if (logicRequired) {
			tinyxml2::XMLNode *nodeLogic = node->FirstChild();
			if (nodeLogic) {
				tinyxml2::XMLElement *logic = nodeLogic->ToElement();
				Algorithm = algorithm->ParseLongLong(logic);
			} else {
				throw logic::ParseError((std::string)"value expected in " + node->Value());
			}
		} else {
			Algorithm = algorithm->GetDefault();
		}
	}

	virtual ~ValueLong() {}
};

template <typename INCHUNK>
class ValueProxyLong : public ValueLong<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		this->Value = this->Algorithm(chunk);
	}

	ValueProxyLong(tinyxml2::XMLElement *node
			, std::shared_ptr<logic::Logic<INCHUNK, unsigned long long> > longLogic)
		: ValueLong<INCHUNK>(node, longLogic, true) {}

	virtual ~ValueProxyLong() {}
};

template <typename INCHUNK>
class ValueMaxLong : public ValueLong<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		const unsigned long long r = this->Algorithm(chunk);
		if ((this->Value) < r)
			this->Value = r;
	}

	virtual unsigned long long Get() {
		unsigned long long r = this->Value;
		this->Value = 0;
		return (r);
	}

	ValueMaxLong(tinyxml2::XMLElement *node
			, std::shared_ptr<logic::Logic<INCHUNK, unsigned long long> > boolLogic)
		: ValueLong<INCHUNK>(node, boolLogic, true) {
	}

	virtual ~ValueMaxLong() {}
};

template <typename INCHUNK>
class ValueMinLong : public ValueLong<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		unsigned long long r = this->Algorithm(chunk);
		if (this->Value > r)
			this->Value = r;
	}

	virtual unsigned long long Get() {
		unsigned long long r = this->Value;
		this->Value = ULLONG_MAX;
		return (r);
	}

	ValueMinLong(tinyxml2::XMLElement *node
			, std::shared_ptr<logic::Logic<INCHUNK, unsigned long long> > boolLogic)
		: ValueLong<INCHUNK>(node, boolLogic, true) {
		this->Value = ULLONG_MAX;
	}

	virtual ~ValueMinLong() {}
};

template <typename INCHUNK>
class ValueSumLong : public ValueLong<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		unsigned long long r = this->Algorithm(chunk);
		this->Value += r;
	}

	virtual unsigned long long Get() {
		unsigned long long r = this->Value;
		this->Value = 0;
		return (r);
	}

	ValueSumLong(tinyxml2::XMLElement *node
			, std::shared_ptr<logic::Logic<INCHUNK, unsigned long long> > longLogic)
		: ValueLong<INCHUNK>(node, longLogic, true) { }

	virtual ~ValueSumLong() {}
};

template <typename INCHUNK>
class ValueCounterLong : public ValueLong<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		this->Value++;
	}

	ValueCounterLong(tinyxml2::XMLElement *node
			, std::shared_ptr<logic::Logic<INCHUNK, unsigned long long> > longLogic)
		: ValueLong<INCHUNK>(node, longLogic, false) { }

	virtual ~ValueCounterLong() {}
};


template <typename INCHUNK>
class ValueBool : public Value<INCHUNK> {
public:
	typedef logic::Logic<INCHUNK, bool> t_logic;
	typedef std::function<bool(std::shared_ptr<INCHUNK>)> t_algorithm;
	bool Value = true;

	t_algorithm Algorithm;

	virtual std::string OutputString() {
		if (Value) {
			return ("1");
		} else {
			return ("0");
		}
	}

	virtual unsigned long long OutputLongLong() {
		if (Value) {
			return (1);
		} else {
			return (0);
		}
	}

	ValueBool(tinyxml2::XMLElement *node
			, std::shared_ptr<t_logic> algorithm
			, bool logicRequired) {
		if (logicRequired) {
			tinyxml2::XMLNode *nodeLogic = node->FirstChild();
			if (nodeLogic) {
				tinyxml2::XMLElement *logic = nodeLogic->ToElement();
				Algorithm = algorithm->ParseLongLong(logic);
			} else {
				throw logic::ParseError((std::string)"value expected in " + node->Value());
			}
		} else {
			Algorithm = algorithm->GetDefault();
		}
	}

	virtual ~ValueBool() {}
};

template <typename INCHUNK>
class ValueProxyBool : public ValueBool<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		this->Value = this->Algorithm(chunk);
	}

	ValueProxyBool(tinyxml2::XMLElement *node
			, std::shared_ptr<logic::Logic<INCHUNK, bool> > boolLogic)
		: ValueBool<INCHUNK>(node, boolLogic, true) {}

	virtual ~ValueProxyBool() {}
};

template <typename INCHUNK>
class ValueString : public Value<INCHUNK> {
public:
	typedef logic::Logic<INCHUNK, std::string> t_logic;
	typedef std::function<std::string(std::shared_ptr<INCHUNK>)> t_algorithm;
	std::string Value = "";

	t_algorithm Algorithm;

	virtual std::string OutputString() {
		return (Get());
	}

	virtual unsigned long long OutputLongLong() {
		return (0);
	}

	virtual std::string Get() {
		return (Value);
	}

	ValueString(tinyxml2::XMLElement *node
			, std::shared_ptr<t_logic> algorithm
			, bool logicRequired) {
		if (logicRequired) {
			tinyxml2::XMLNode *nodeLogic = node->FirstChild();
			if (nodeLogic) {
				tinyxml2::XMLElement *logic = nodeLogic->ToElement();
				Algorithm = algorithm->ParseString(logic);
			} else {
				throw logic::ParseError((std::string)"value expected in " + node->Value());
			}
		} else {
			Algorithm = algorithm->GetDefault();
		}
	}

	virtual ~ValueString() {}
};

template <typename INCHUNK>
class ValueProxyString : public ValueString<INCHUNK> {
public:
	virtual void Input(std::shared_ptr<INCHUNK> chunk) {
		this->Value = this->Algorithm(chunk);
	}

	ValueProxyString(tinyxml2::XMLElement *node
			, std::shared_ptr<logic::Logic<INCHUNK, std::string> > stringLogic)
		: ValueString<INCHUNK>(node, stringLogic, true) {}

	virtual ~ValueProxyString() {}
};


template <typename IN>
class View {
	typedef std::shared_ptr<Value<IN> > t_selection;

	std::shared_ptr<logic::Logic<IN, bool> > BoolParser;
	std::shared_ptr<logic::Logic<IN, unsigned long long> > LongParser;
	std::shared_ptr<logic::Logic<IN, std::string> > StringParser;
public:
	std::vector<t_selection> Selection;
	virtual std::string TypeID() = 0;
	virtual void Output() = 0;

	void Input(std::shared_ptr<IN> chunk)
	{
		for (auto s : Selection) {
			s->Input(chunk);
		}

		// TODO
		if (true) {
			Output();
		}
	}

	virtual void ParseParams(tinyxml2::XMLElement *node) {};

	std::shared_ptr<Value<IN> > ParseSelect(tinyxml2::XMLElement *node) {
		tinyxml2::XMLElement *logic = node->FirstChild()->ToElement();
		if (logic != NULL) {
			std::string name(logic->Value());
			if (name == "bool") {
				return (std::make_shared<ValueProxyBool<IN> >(logic, BoolParser));
			} else if (name == "long") {
				return (std::make_shared<ValueProxyLong<IN> >(logic, LongParser));
			} else if (name == "string") {
				return (std::make_shared<ValueProxyString<IN> >(logic, StringParser));
			} else if (name == "max") {
				return (std::make_shared<ValueMaxLong<IN> >(logic, LongParser));
			} else if (name == "min") {
				return (std::make_shared<ValueMinLong<IN> >(logic, LongParser));
			} else if (name == "sum") {
				return (std::make_shared<ValueSumLong<IN> >(logic, LongParser));
			} else if (name == "counter") {
				return (std::make_shared<ValueCounterLong<IN> >(logic, LongParser));
			}
			throw logic::ParseError("unknown selection type: " + name);
		}
		throw logic::ParseError("<select/> must have a child");
	}

	void ParseSelects(tinyxml2::XMLElement *node) {
		tinyxml2::XMLHandle docHandle(node);
		tinyxml2::XMLElement* select = docHandle.FirstChildElement("select").ToElement();
		while (NULL != select) {
			t_selection v = ParseSelect(select);
			Selection.push_back(v);
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
