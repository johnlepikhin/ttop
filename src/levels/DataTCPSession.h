
#ifndef SRC_LEVELS_DATATCPSESSION_H_
#define SRC_LEVELS_DATATCPSESSION_H_

#include "../Logic.h"
#include "../src/levels/SessionTCP.h"
#include "DataTCP.h"

namespace ttop {

namespace level_data {

template <typename OUT>
class DataTCPEndPoint: public logic::Logic<EndPoint, OUT>
{
	OUT DefaultValue;
public:
	DataTCPEndPoint(OUT defaultValue) : logic::Logic<EndPoint, OUT>(defaultValue) {}

	virtual typename logic::Logic<EndPoint, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "PayloadPreview") {
			const char *defaultPreview = elt.Attribute("default");
			if (!defaultPreview) {
				throw logic::ParseError("No default=... attribute for <PayloadPreview/>");
			}
			auto r = [defaultPreview](std::shared_ptr<EndPoint> c) {
				std::shared_ptr<std::string> r = c->GetPayloadPreview();
				if (r == nullptr) {
					return (std::string(defaultPreview));
				}
				return (*(r.get()));
			};
			return (r);
		} else if (name == "LastChunk") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCP<OUT> LogicTCP(DefaultValue);
				auto subfn = LogicTCP.ParseString(child);
				auto r = [subfn](std::shared_ptr<EndPoint> c) {
					return(subfn(c->LastChunk));
				};
				return (r);
			}
			throw logic::ParseError("No child for <LastChunk/>");
		}
		return (ttop::logic::Logic<EndPoint, OUT>::ParseStringCustom(elt));
	}

	virtual typename logic::Logic<EndPoint, OUT>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "HasLastChunk") {
			auto r = [](std::shared_ptr<EndPoint> c) {
				return (c->LastChunk != nullptr);
			};
			return (r);
		} else if (name == "LastChunk") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCP<OUT> LogicTCP(DefaultValue);
				auto subfn = LogicTCP.ParseBool(child);
				auto r = [subfn](std::shared_ptr<EndPoint> c) {
					return(subfn(c->LastChunk));
				};
				return (r);
			}
			throw logic::ParseError("No child for <LastChunk/>");
		}
		return (ttop::logic::Logic<EndPoint, OUT>::ParseBoolCustom(elt));
	}

	virtual typename logic::Logic<EndPoint, OUT>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "NextExpectedSEQ") {
			auto r = [](std::shared_ptr<EndPoint> c) {
				return (c->NextExpectedSEQ);
			};
			return (r);
		} else if (name == "RawIfaceBytes") {
			auto r = [](std::shared_ptr<EndPoint> c) {
				return (c->RawIfaceBytes);
			};
			return (r);
		} else if (name == "PayloadBytes") {
			auto r = [](std::shared_ptr<EndPoint> c) {
				return (c->PayloadBytes);
			};
			return (r);
		} else if (name == "LastChunk") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCP<OUT> LogicTCP(DefaultValue);
				auto subfn = LogicTCP.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<EndPoint> c) {
					return(subfn(c->LastChunk));
				};
				return (r);
			}
			throw logic::ParseError("No child for <LastChunk/>");
		}
		return (ttop::logic::Logic<EndPoint, OUT>::ParseLongLongCustom(elt));
	}

	virtual ~DataTCPEndPoint() {};
};

template <typename OUT>
class DataTCPSession: public logic::Logic<SessionTCP, OUT>
{
	OUT DefaultValue;
public:
	DataTCPSession(OUT defaultValue) : logic::Logic<SessionTCP, OUT>(defaultValue) {}

	virtual typename logic::Logic<SessionTCP, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());

		if (name == "Client") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCPEndPoint<OUT> LogicTCPEndPoint(DefaultValue);
				auto subfn = LogicTCPEndPoint.ParseString(child);
				auto r = [subfn](std::shared_ptr<SessionTCP> c) {
					return(subfn(c->Client));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Client/>");
		} else if (name == "Server") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCPEndPoint<OUT> LogicTCPEndPoint(DefaultValue);
				auto subfn = LogicTCPEndPoint.ParseString(child);
				auto r = [subfn](std::shared_ptr<SessionTCP> c) {
					return(subfn(c->Server));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Server/>");
		}
		return (ttop::logic::Logic<SessionTCP, OUT>::ParseStringCustom(elt));
	}

	virtual typename logic::Logic<SessionTCP, OUT>::t_bool_value ParseBoolCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "DirectionDetected") {
			auto r = [](std::shared_ptr<SessionTCP> c) {
				return (c->DirectionDetected);
			};
			return (r);
		} else if (name == "Client") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCPEndPoint<OUT> LogicTCPEndPoint(DefaultValue);
				auto subfn = LogicTCPEndPoint.ParseBool(child);
				auto r = [subfn](std::shared_ptr<SessionTCP> c) {
					return(subfn(c->Client));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Client/>");
		} else if (name == "Server") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCPEndPoint<OUT> LogicTCPEndPoint(DefaultValue);
				auto subfn = LogicTCPEndPoint.ParseBool(child);
				auto r = [subfn](std::shared_ptr<SessionTCP> c) {
					return(subfn(c->Server));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Server/>");
		}
		return (ttop::logic::Logic<SessionTCP, OUT>::ParseBoolCustom(elt));
	}

	virtual typename logic::Logic<SessionTCP, OUT>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "LastInternalID") {
			auto r = [](std::shared_ptr<SessionTCP> c) {
				return (c->LastInternalID);
			};
			return (r);
		} else if (name == "Client") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCPEndPoint<OUT> LogicTCPEndPoint(DefaultValue);
				auto subfn = LogicTCPEndPoint.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<SessionTCP> c) {
					return(subfn(c->Client));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Client/>");
		} else if (name == "Server") {
			auto child = elt.FirstChildElement();
			if (child) {
				DataTCPEndPoint<OUT> LogicTCPEndPoint(DefaultValue);
				auto subfn = LogicTCPEndPoint.ParseLongLong(child);
				auto r = [subfn](std::shared_ptr<SessionTCP> c) {
					return(subfn(c->Server));
				};
				return (r);
			}
			throw logic::ParseError("No child for <Server/>");
		}
		return (ttop::logic::Logic<SessionTCP, OUT>::ParseLongLongCustom(elt));
	}

	virtual ~DataTCPSession() {};
};

class FilterTCPSession : public DataTCPSession<bool> {
public:
	FilterTCPSession() : DataTCPSession<bool>(true) {}
};

}

}

#endif
