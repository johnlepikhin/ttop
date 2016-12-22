// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataSSL.h"
#include "DataTCPSession.h"

namespace ttop {
namespace level_data {

std::string StringOfRecordType(const SSLRecordType &type) {
	switch (type) {
	case CHANGE_CIPHER_SPEC: return ("CHANGE_CIPHER_SPEC");
	case ALERT: return ("ALERT");
	case HANDSHAKE: return ("HANDSHAKE");
	case APPLICATION_DATA: return ("APPLICATION_DATA");
	}
	return ("");
}

typename logic::Logic<ChunkSSL>::t_string_value DataSSL::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPSession LogicSessionTCP;
			auto subfn = LogicSessionTCP.ParseString(child);
			auto r = [subfn](const std::shared_ptr<ChunkSSL> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	} else if (name == "RecordType") {
		return ([](const std::shared_ptr<ChunkSSL> &c) { return(StringOfRecordType(c->RecordType)); });
	}

	return (ttop::logic::Logic<ChunkSSL>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkSSL>::t_bool_value DataSSL::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPSession LogicSessionTCP;
			auto subfn = LogicSessionTCP.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<ChunkSSL> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	} else if (name == "Is_CHANGE_CIPHER_SPEC") {
		return ([](const std::shared_ptr<ChunkSSL> &c) { return(c->RecordType == CHANGE_CIPHER_SPEC); });
	} else if (name == "Is_ALERT") {
		return ([](const std::shared_ptr<ChunkSSL> &c) { return(c->RecordType == ALERT); });
	} else if (name == "Is_HANDSHAKE") {
		return ([](const std::shared_ptr<ChunkSSL> &c) { return(c->RecordType == HANDSHAKE); });
	} else if (name == "Is_APPLICATION_DATA") {
		return ([](const std::shared_ptr<ChunkSSL> &c) { return(c->RecordType == APPLICATION_DATA); });
	}

	return (ttop::logic::Logic<ChunkSSL>::ParseBoolCustom(elt));
}

typename logic::Logic<ChunkSSL>::t_longlong_value DataSSL::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPSession LogicSessionTCP;
			auto subfn = LogicSessionTCP.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<ChunkSSL> &c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	} else if (name == "Version") {
		return ([](const std::shared_ptr<ChunkSSL> &c) { return(c->Version); });
	} else if (name == "DataLength") {
		return ([](const std::shared_ptr<ChunkSSL> &c) { return(c->DataLength); });
	}

	return (ttop::logic::Logic<ChunkSSL>::ParseBoolCustom(elt));
}

} /* namespace level_data */
} /* namespace ttop */
