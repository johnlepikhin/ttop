// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataHTTP.h"

#include "../src/core/utils.h"
#include <algorithm>

namespace ttop {
namespace level_data {

typename logic::Logic<ChunkHTTP>::t_string_value DataHTTP::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Method") {
		return ([](const std::shared_ptr<ChunkHTTP> &c) { return(c->Request->Method); });
	} else if (name == "URI") {
		return ([](const std::shared_ptr<ChunkHTTP> &c) { return(c->Request->URI); });
	} else if (name == "Host") {
		return ([](const std::shared_ptr<ChunkHTTP> &c) { return(c->Request->Host); });
	} else if (name == "Message") {
		return ([](const std::shared_ptr<ChunkHTTP> &c) { return(c->Response->Message); });
	} else if (name == "ReqHeader" || name == "RespHeader") {
		const char *_type = elt.Attribute("default");
		std::string _default = (_type) ? _type : "";
		std::string hdrname(elt.GetText());
		return ([&name, &_default, &hdrname](const std::shared_ptr<ChunkHTTP> &c) {
			std::vector<std::pair<std::string, std::string> > headers
			= (name == "ReqHeader") ? c->Request->Headers : c->Response->Headers;
			auto it = std::find_if(headers.begin()
					, headers.end()
					, [&hdrname](const std::pair<std::string, std::string>& h) {
				return (util::iequals(h.first, hdrname));
			});

			if (it == headers.end()) {
				return (_default);
			} else {
				return (it->second);
			}
		});
	}

	return (ttop::logic::Logic<ChunkHTTP>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkHTTP>::t_longlong_value DataHTTP::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Code") {
		return ([](const std::shared_ptr<ChunkHTTP> &c) { return(c->Response->Code); });
	}
	return (ttop::logic::Logic<ChunkHTTP>::ParseLongLongCustom(elt));
}

typename logic::Logic<ChunkHTTP>::t_bool_value DataHTTP::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "HasRequest") {
		return ([](const std::shared_ptr<ChunkHTTP> &c) { return(c->Request != nullptr); });
	} else if (name == "HasResponse") {
		return ([](const std::shared_ptr<ChunkHTTP> &c) { return(c->Response != nullptr); });
	}
	return (ttop::logic::Logic<ChunkHTTP>::ParseBoolCustom(elt));
}

DataHTTP::~DataHTTP()
{
}

} /* namespace level_data */
} /* namespace ttop */
