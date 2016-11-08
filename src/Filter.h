
#ifndef SRC_FILTER_H_
#define SRC_FILTER_H_

#include "Logic.h"

namespace ttop {
namespace logic {

template <typename IN>
class Filter : public ttop::logic::Logic<IN, bool> {
public:
	Filter() {
		this->Algorithm = this->True;
	}

	void Parse(tinyxml2::XMLElement *elt) {
		tinyxml2::XMLElement *logic = elt->FirstChildElement();
		this->Algorithm = this->ParseBool(logic);
	}
};

} /* namespace logic */
} /* namespace ttop */

#endif /* SRC_FILTER_H_ */
