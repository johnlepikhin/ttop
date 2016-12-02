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
		if (!defaultPreview)
			throw logic::ParseError("No default=... attribute for <PayloadPreview/>");
		std::string defaultValue(defaultPreview);
		auto r = [defaultValue](const std::shared_ptr<EndPoint> &c) {
			std::string *r = c->GetPayloadPreview();
			if (r == nullptr)
				return (defaultValue);
			return (*r);
		};
		return (r);
	} else if (name == "LastChunk") {
		const char *_defaultValue;
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		std::string defaultValue(_defaultValue);

		auto child = elt.FirstChildElement();
		if (child) {
			DataTCP LogicTCP;
			auto subfn = LogicTCP.ParseString(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<EndPoint> &c) {
				if (c->LastChunk == nullptr)
					return (defaultValue);
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
		const char *_defaultValue;
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		bool defaultValue((std::string(_defaultValue) == "true") ? true : false);

		auto child = elt.FirstChildElement();
		if (child) {
			DataTCP LogicTCP;
			auto subfn = LogicTCP.ParseBool(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<EndPoint> &c) {
				if (c->LastChunk == nullptr)
					return (defaultValue);
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
		const char *_defaultValue;
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		long long defaultValue(stoll(std::string(_defaultValue)));

		auto child = elt.FirstChildElement();
		if (child) {
			DataTCP LogicTCP;
			auto subfn = LogicTCP.ParseLongLong(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<EndPoint> &c) {
				if (c->LastChunk == nullptr)
					return (defaultValue);
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
	const char *_defaultValue;

	if (name == "Client") {
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		std::string defaultValue(_defaultValue);
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseString(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<SessionTCP> &c) {
				if (c->Client == nullptr)
					return (defaultValue);
				return(subfn(c->Client));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Client/>");
	} else if (name == "Server") {
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		std::string defaultValue(_defaultValue);
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseString(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<SessionTCP> &c) {
				if (c->Server == nullptr)
					return (defaultValue);
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
	const char *_defaultValue;

	if (name == "DirectionDetected") {
		auto r = [](const std::shared_ptr<SessionTCP> &c) {
			return (c->DirectionDetected);
		};
		return (r);
	} else if (name == "FollowerDetected") {
			auto r = [](const std::shared_ptr<SessionTCP> &c) {
				return (c->Follower != nullptr);
			};
			return (r);
	} else if (name == "Client") {
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		bool defaultValue((std::string(_defaultValue) == "true") ? true : false);
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseBool(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<SessionTCP> &c) {
				if (c->Client == nullptr)
					return (defaultValue);
				return(subfn(c->Client));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Client/>");
	} else if (name == "Server") {
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		bool defaultValue((std::string(_defaultValue) == "true") ? true : false);
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseBool(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<SessionTCP> &c) {
				if (c->Server == nullptr)
					return (defaultValue);
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
	const char *_defaultValue;

	if (name == "LastInternalID") {
		auto r = [](const std::shared_ptr<SessionTCP> &c) {
			return (c->LastInternalID);
		};
		return (r);
	} else if (name == "SessionID") {
		auto r = [](const std::shared_ptr<SessionTCP> &c) {
			return (c->SessionID);
		};
		return (r);
	} else if (name == "Client") {
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		long long defaultValue(stoll(std::string(_defaultValue)));
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseLongLong(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<SessionTCP> &c) {
				if (c->Client == nullptr)
					return (defaultValue);
				return(subfn(c->Client));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Client/>");
	} else if (name == "Server") {
		if(!(_defaultValue = elt.Attribute("default"))) throw logic::ParseError("No attribute default='...' for <"+name+"/>");
		long long defaultValue(stoll(std::string(_defaultValue)));
		auto child = elt.FirstChildElement();
		if (child) {
			DataTCPEndPoint LogicTCPEndPoint;
			auto subfn = LogicTCPEndPoint.ParseLongLong(child);
			auto r = [defaultValue, subfn](const std::shared_ptr<SessionTCP> &c) {
				if (c->Server == nullptr)
					return (defaultValue);
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
