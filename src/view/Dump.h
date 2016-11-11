
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

	Dump(std::shared_ptr<logic::Logic<IN, bool> > boolParser)
		: View<IN>(boolParser)
	{

	}

	virtual ~Dump() {};
};

} /* namespace view */
} /* namespace ttop */

#endif /* SRC_VIEW_DUMP_H_ */
