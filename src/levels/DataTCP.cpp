// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataTCP.h"

namespace ttop {

namespace level_data {

typename logic::Logic<ChunkTCP>::t_string_value DataTCP::ParseStringCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPVariant LogiIPVariant;
			auto subfn = LogiIPVariant.ParseString(child);
			auto r = [subfn](std::shared_ptr<ChunkTCP> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkTCP>::ParseStringCustom(elt));
}

typename logic::Logic<ChunkTCP>::t_bool_value DataTCP::ParseBoolCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPVariant LogicIPVariant;
			auto subfn = LogicIPVariant.ParseBool(child);
			auto r = [subfn](std::shared_ptr<ChunkTCP> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	} else if (name == "FlagACK") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->FlagACK);
		};
		return (r);
	} else if (name == "FlagFIN") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->FlagFIN);
		};
		return (r);
	} else if (name == "FlagPSH") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->FlagPSH);
		};
		return (r);
	} else if (name == "FlagRST") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->FlagRST);
		};
		return (r);
	} else if (name == "FlagSYN") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->FlagSYN);
		};
		return (r);
	} else if (name == "FlagURG") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->FlagURG);
		};
		return (r);
	}
	return (ttop::logic::Logic<ChunkTCP>::ParseBoolCustom(elt));
}

typename logic::Logic<ChunkTCP>::t_longlong_value DataTCP::ParseLongLongCustom(tinyxml2::XMLElement &elt)
{
	std::string name(elt.Value());
	if (name == "PayloadLength") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->PayloadLength);
		};
		return (r);
	} else if (name == "PktLength") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->PktLength);
		};
		return (r);
	} else if (name == "DestinationPort") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->DestinationPort);
		};
		return (r);
	} else if (name == "SourcePort") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->SourcePort);
		};
		return (r);
	} else if (name == "ConfirmNumber") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->ConfirmNumber);
		};
		return (r);
	} else if (name == "HeaderLength") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->HeaderLength);
		};
		return (r);
	} else if (name == "SeqNumber") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->SeqNumber);
		};
		return (r);
	} else if (name == "WindowSize") {
		auto r = [](std::shared_ptr<ChunkTCP> c) {
			return (c->WindowSize);
		};
		return (r);
	} else if (name == "Parent") {
		auto child = elt.FirstChildElement();
		if (child) {
			DataPacketIPVariant LogicIPVariant;
			auto subfn = LogicIPVariant.ParseLongLong(child);
			auto r = [subfn](std::shared_ptr<ChunkTCP> c) {
				return(subfn(c->Parent));
			};
			return (r);
		}
		throw logic::ParseError("No child for <Parent/>");
	}
	return (ttop::logic::Logic<ChunkTCP>::ParseLongLongCustom(elt));
}

DataTCP::~DataTCP() {};

}

}
