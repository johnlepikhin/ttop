
#include "DataMySQL.h"

#include "../src/core/utils.h"
#include <algorithm>

namespace ttop {
namespace level_data {

typename logic::Logic<PacketMySQL>::t_string_value DataMySQL::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Query") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return((c->Request != nullptr) ? c->Request->Query : ""); });
	} else if (name == "QueryType") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return((c->Request != nullptr) ? c->Request->QueryType : ""); });
	} else if (name == "Database") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->Database); });
	} else if (name == "ServerVersion") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->ServerVersion); });
	} else if (name == "Username") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->Username); });
	}

	return (ttop::logic::Logic<PacketMySQL>::ParseStringCustom(elt));
}

typename logic::Logic<PacketMySQL>::t_longlong_value DataMySQL::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "CommandType") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return((c->Request != nullptr) ? c->Request->CommandType : 255); });
	} else if (name == "Charset") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->Charset); });
	} else if (name == "ConnectionID") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->ConnectionID); });
	} else if (name == "MaxPktLength") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->MaxPktLen); });
	} else if (name == "PacketLength") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->PacketLength); });
	}
	return (ttop::logic::Logic<PacketMySQL>::ParseLongLongCustom(elt));
}

typename logic::Logic<PacketMySQL>::t_bool_value DataMySQL::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "HasRequest") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->Request != nullptr); });
	} else if (name == "HasResponse") {
		return ([](const std::shared_ptr<PacketMySQL> &c) { return(c->Response != nullptr); });
	}
	return (ttop::logic::Logic<PacketMySQL>::ParseBoolCustom(elt));
}

DataMySQL::~DataMySQL()
{
}


} /* namespace level_data */
} /* namespace ttop */
