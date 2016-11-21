
#ifndef SRC_LEVELS_DATATCPSESSION_H_
#define SRC_LEVELS_DATATCPSESSION_H_

#include "../Logic.h"
#include "../src/levels/SessionTCP.h"
#include "DataTCP.h"

namespace ttop {

namespace level_data {

class DataTCPEndPoint: public logic::Logic<EndPoint>
{
public:
	virtual typename logic::Logic<EndPoint>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<EndPoint>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<EndPoint>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt);
	virtual ~DataTCPEndPoint();
};

class DataTCPSession: public logic::Logic<SessionTCP>
{
public:
	virtual typename logic::Logic<SessionTCP>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<SessionTCP>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt);
	virtual typename logic::Logic<SessionTCP>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt);
	virtual ~DataTCPSession();
};

}

}

#endif
