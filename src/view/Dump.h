
#ifndef SRC_VIEW_DUMP_H_
#define SRC_VIEW_DUMP_H_

#include "View.h"

namespace ttop {
namespace view {

template <typename IN>
class Dump: public View<IN> {
public:
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

	virtual ~Dump() {};

	virtual void Output()
	{
		bool isFirst = true;
		for (auto s : this->Selection_list) {
			if (!isFirst)
				std::cout << " ";
			std::cout << s->Value;
			isFirst = false;
		}
		std::cout << std::endl;
	}
};

} /* namespace view */
} /* namespace ttop */

#endif /* SRC_VIEW_DUMP_H_ */
