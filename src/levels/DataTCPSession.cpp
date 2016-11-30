// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataTCPSession.h"

namespace ttop {

namespace level_data {

typename logic::Logic<EndPoint>::t_string_value DataTCPEndPoint::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "PayloadPreview") {
		const char *defaultPreview = elt.Attribute("default");
		if (!defaultPreview) {
			throw logic::ParseError("No default=... attribute for <PayloadPreview/>");
		}
		auto r = [defaultPreview](const std::shared_ptr<EndPoint> &c) {
			std::string r = c->GetPayloadPreview();
			if (r.empty()) {
				return (std::string(defaultPreview));
			}
			return (r);
		};
		return (r);
	} else if (name == "LastChunk") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCP LogicTCP;
			auto subfn = LogicTCP.ParseString(child);
			auto r = [subfn](const std::shared_ptr<EndPoint> &c) {
				return(subfn(c->LastChunk));
			};
			return (r);
		}
		throw logic::ParseError("No child for <LastChunk/>");
	}
	return (ttop::logic::Logic<EndPoint>::ParseStringCustom(elt));
}

typename logic::Logic<EndPoint>::t_bool_value DataTCPEndPoint::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "HasLastChunk") {
		auto r = [](const std::shared_ptr<EndPoint> &c) {
			return (c->LastChunk != nullptr);
		};
		return (r);
	} else if (name == "LastChunk") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCP LogicTCP;
			auto subfn = LogicTCP.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<EndPoint> &c) {
				return(subfn(c->LastChunk));
			};
			return (r);
		}
		throw logic::ParseError("No child for <LastChunk/>");
	}
	return (ttop::logic::Logic<EndPoint>::ParseBoolCustom(elt));
}

typename logic::Logic<EndPoint>::t_longlong_value DataTCPEndPoint::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "NextExpectedSEQ") {
		auto r = [](const std::shared_ptr<EndPoint> &c) {
			return (c->NextExpectedSEQ);
		};
		return (r);
	} else if (name == "RawIfaceBytes") {
		auto r = [](const std::shared_ptr<EndPoint> &c) {
			return (c->RawIfaceBytes);
		};
		return (r);
	} else if (name == "PayloadBytes") {
		auto r = [](const std::shared_ptr<EndPoint> &c) {
			return (c->PayloadBytes);
		};
		return (r);
	} else if (name == "LastChunk") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCP LogicTCP;
			auto subfn = LogicTCP.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<EndPoint> &c) {
				return(subfn(c->LastChunk));
			};
			return (r);
		}
		throw logic::ParseError("No child for <LastChunk/>");
	}
	return (ttop::logic::Logic<EndPoint>::ParseLongLongCustom(elt));
}

DataTCPEndPoint::~DataTCPEndPoint() {};

//////////////


typename logic::Logic<SessionTCP>::t_string_value DataTCPSession::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());

	if (name == "Client") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseString(child);
			auto r = [subfn](const std::shared_ptr<SessionTCP> &c) {
				return(subfn(c->Client));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Client/>");
	} else if (name == "Server") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseString(child);
			auto r = [subfn](const std::shared_ptr<SessionTCP> &c) {
				return(subfn(c->Server));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Server/>");
	}
	return (ttop::logic::Logic<SessionTCP>::ParseStringCustom(elt));
}

typename logic::Logic<SessionTCP>::t_bool_value DataTCPSession::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "DirectionDetected") {
		auto r = [](const std::shared_ptr<SessionTCP> &c) {
			return (c->DirectionDetected);
		};
		return (r);
	} else if (name == "Client") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<SessionTCP> &c) {
				return(subfn(c->Client));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Client/>");
	} else if (name == "Server") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseBool(child);
			auto r = [subfn](const std::shared_ptr<SessionTCP> &c) {
				return(subfn(c->Server));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Server/>");
	}
	return (ttop::logic::Logic<SessionTCP>::ParseBoolCustom(elt));
}

typename logic::Logic<SessionTCP>::t_longlong_value DataTCPSession::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "LastInternalID") {
		auto r = [](const std::shared_ptr<SessionTCP> &c) {
			return (c->LastInternalID);
		};
		return (r);
	} else if (name == "Client") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<SessionTCP> &c) {
				return(subfn(c->Client));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Client/>");
	} else if (name == "Server") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseLongLong(child);
			auto r = [subfn](const std::shared_ptr<SessionTCP> &c) {
				return(subfn(c->Server));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Server/>");
	}
	return (ttop::logic::Logic<SessionTCP>::ParseLongLongCustom(elt));
}

DataTCPSession::~DataTCPSession() {};


}

}
