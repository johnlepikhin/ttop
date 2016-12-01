
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
	std::string GroupSeparator = "";

	virtual std::string TypeID();
	Dump(std::shared_ptr<logic::Logic<IN> > parser);
	virtual ~Dump();
	virtual void DoOutput(const std::vector<typename View<IN>::t_selection> &output);
	virtual void ParseParams(tinyxml2::XMLElement *node);
};

} /* namespace view */
} /* namespace ttop */

#endif /* SRC_VIEW_DUMP_H_ */
