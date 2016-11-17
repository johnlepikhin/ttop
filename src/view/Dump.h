
#ifndef SRC_VIEW_DUMP_H_
#define SRC_VIEW_DUMP_H_

#include "View.h"

#include <iostream>
#include <fstream>

namespace ttop {
namespace view {

template <typename IN>
class Dump: public View<IN> {
public:
	std::string OutputFile;
	std::ofstream OutputStream;
	std::string FieldSeparator = " ";
	std::string RecordSeparator = "\n";

	virtual std::string TypeID()
	{
		return ((std::string)"dump");
	}

	Dump(std::shared_ptr<logic::Logic<IN, bool> > boolParser
			, std::shared_ptr<logic::Logic<IN, unsigned long long> > longParser
			, std::shared_ptr<logic::Logic<IN, std::string> > stringParser
			)
		: View<IN>(boolParser, longParser, stringParser)
	{

	}

	virtual ~Dump() {
		if (OutputStream.is_open())
			OutputStream.close();
	};

	virtual void Output()
	{
		std::ostream &o = (OutputStream.is_open()) ? OutputStream : std::cout;

		for (auto g_it = this->Selection.begin(); g_it!=this->Selection.end(); ++g_it) {
			bool isFirst = true;
			for (auto it = g_it->second.begin(); it!=g_it->second.end(); ++it) {
				if (!isFirst)
					o << FieldSeparator;
				o << (*it).Val;
				isFirst = false;
			}
			o << RecordSeparator;
		}
	}

	virtual void ParseParams(tinyxml2::XMLElement *node)
	{
		const char *_attr = node->Attribute("output");
		if (_attr) {
			OutputFile = _attr;
			if ((std::string)"-" != _attr) {
				OutputStream.open(_attr, std::ios::out | std::ios::app);
			}
		}
		_attr = node->Attribute("rseparator");
		if (_attr) {
			RecordSeparator = _attr;
		}
		_attr = node->Attribute("fseparator");
		if (_attr) {
			FieldSeparator = _attr;
		}
	}
};

} /* namespace view */
} /* namespace ttop */

#endif /* SRC_VIEW_DUMP_H_ */
