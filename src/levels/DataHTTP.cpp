// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataHTTP.h"
#include "DataTCPSession.h"

#include "../src/core/utils.h"
#include <algorithm>

namespace ttop {
namespace level_data {

typename logic::Logic<ChunkHTTP>::t_string_value DataHTTP::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	const char *_type = elt.Attribute("default");
	std::string _default = (_type) ? _type : "";

	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPSession LogicSessionTCP;
			auto subfn = LogicSessionTCP.ParseString(child);
			auto r = [subfn](const std::shared_ptr<ChunkHTTP> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	} else if (name == "Method") {
		return ([_default](const std::shared_ptr<ChunkHTTP> &c) {
			if (c->Request != nullptr) return(c->Request->Method);
			return (_default);
		});
	} else if (name == "URI") {
		return ([_default](const std::shared_ptr<ChunkHTTP> &c) {
			if (c->Request != nullptr) return(c->Request->URI);
			return (_default);
		});
	} else if (name == "Host") {
		return ([_default](const std::shared_ptr<ChunkHTTP> &c) {
			if (c->Request != nullptr) return(c->Request->Host);
			return (_default);
		});
	} else if (name == "Message") {
		return ([_default](const std::shared_ptr<ChunkHTTP> &c) {
			if (c->Response != nullptr) return(c->Response->Message);
			return (_default);
		});
	} else if (name == "ReqHeader" || name == "RespHeader") {
		std::string hdrname(elt.GetText());
		return ([name, _default, hdrname](const std::shared_ptr<ChunkHTTP> &c) {
			std::vector<std::pair<std::string, std::string> > headers
			= (name == "ReqHeader") ? c->Request->Headers : c->Response->Headers;
			auto it = std::find_if(headers.begin()
					, headers.end()
					, [hdrname](const std::pair<std::string, std::string>& h) {
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

	const char *_type = elt.Attribute("default");
	uint64_t _default;
	try {
		_default = (_type) ? std::stoll(_type) : 0;
	} catch (...) {
		throw logic::ParseError(std::string("Long numeric value expected for default='..' attribute, but got ") + std::string(_type));
	}

	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPSession LogicSessionTCP;
			auto subfn = LogicSessionTCP.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<ChunkHTTP> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	} else if (name == "Code") {
		return ([_default](const std::shared_ptr<ChunkHTTP> &c) {
			if (c->Response != nullptr) return(static_cast<uint64_t>(c->Response->Code));
			return (_default);
		});
	}
	return (ttop::logic::Logic<ChunkHTTP>::ParseLongLongCustom(elt));
}

typename logic::Logic<ChunkHTTP>::t_bool_value DataHTTP::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPSession LogicSessionTCP;
			auto subfn = LogicSessionTCP.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<ChunkHTTP> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	} else if (name == "HasRequest") {
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
