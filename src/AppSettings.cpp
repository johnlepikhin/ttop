/*
 * AppSettings.cpp
 *
 *  Created on: 20 окт. 2016 г.
 *      Author: eugene
 */

#include "AppSettings.h"
#include "utils.h"
#include <string>
#include <iostream>
#include "tinyxml2.h"

namespace ttop {

AppSettings::AppSettings(std::string &file)
	: File(file)
{
	Load();
}

void AppSettings::Load()
{
	tinyxml2::XMLDocument doc;
	bool loadStatus = doc.LoadFile(File.c_str());
	if (loadStatus == tinyxml2::XML_SUCCESS) {
		const std::string rootName = doc.RootElement()->Value();
		if (rootName != ExpectedRootElementName) {
			ParseError("unexpected root node; found '" + rootName + "', but expected '" + ExpectedRootElementName + "'");
		}

		tinyxml2::XMLHandle docHandle( doc.RootElement() );

		tinyxml2::XMLElement* parsers = docHandle.FirstChildElement("parsers").ToElement();
		if (NULL != parsers) {
			ParseParsers(Parser, parsers);
		} else {
			ParseError("Child element 'parsers' is required");
		}
	} else {
		ParseError(doc.ErrorName());
	}
}

template <typename PARENT>
void AppSettings::ParseParsers(PARENT &parent, tinyxml2::XMLElement *parsers)
{
	parent.ParseXMLSettings(parsers);

	tinyxml2::XMLElement *parser = parsers->FirstChildElement("parser");
	for(; NULL != parser; parser=parser->NextSiblingElement() ) {
		const std::string name = parser->Value();
		if (name == "parser") {
			const tinyxml2::XMLAttribute *a_of = parser->FindAttribute("of");
			if (a_of) {
				std::string avalue(a_of->Value());
				if (!BuildParser(parent, parser, avalue)) {
					ParseError("parser " + avalue + " is not valid child");
				}
			} else {
				ParseError("attribute 'of=...' not found for parser element");
			}
		} else {
			ParseError("expected 'parser' element but found '" + name + "'");
		}
	}
}

bool AppSettings::BuildParser(level::EtherNet &parser, tinyxml2::XMLElement *container, const std::string &name) {
	if (name == "DIX") {
		level::EtherNetDIX *child = new level::EtherNetDIX();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}
	if (name == "RAW") {
		level::EtherNetRAW *child = new level::EtherNetRAW();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}
	if (name == "802LLC") {
		level::EtherNet802LLC *child = new level::EtherNet802LLC();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}
	if (name == "SNAP") {
		level::EtherNetSNAP *child = new level::EtherNetSNAP();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}

	return (false);
}

bool AppSettings::BuildParser(level::EtherNetDIX &parser, tinyxml2::XMLElement *container, const std::string &name) {
	if (name == "IPv4") {
		level::IPv4 *child = new level::IPv4();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}
	if (name == "IPv6") {
		level::IPv6 *child = new level::IPv6();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}

	return (false);
}

bool AppSettings::BuildParser(level::EtherNetRAW &parser, tinyxml2::XMLElement *container, const std::string &name) {
	return (false);
}

bool AppSettings::BuildParser(level::EtherNet802LLC &parser, tinyxml2::XMLElement *container, const std::string &name) {
	return (false);
}

bool AppSettings::BuildParser(level::EtherNetSNAP &parser, tinyxml2::XMLElement *container, const std::string &name) {
	return (false);
}

bool AppSettings::BuildParser(level::IPv4 &parser, tinyxml2::XMLElement *container, const std::string &name) {
	if (name == "IPv4Packet") {
		level::IPv4Packet *child = new level::IPv4Packet();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}

	return (false);
}

bool AppSettings::BuildParser(level::IPv4Packet &parser, tinyxml2::XMLElement *container, const std::string &name) {
	if (name == "UDP") {
		level::UDP *child = new level::UDP();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}

	if (name == "TCP") {
		level::TCP *child = new level::TCP();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}

	return (false);
}

bool AppSettings::BuildParser(level::IPv6 &parser, tinyxml2::XMLElement *container, const std::string &name) {
	return (false);
}

bool AppSettings::BuildParser(level::UDP &parser, tinyxml2::XMLElement *container, const std::string &name) {
	return (false);
}

bool AppSettings::BuildParser(level::TCP &parser, tinyxml2::XMLElement *container, const std::string &name) {
	if (name == "TCPSession") {
		level::TCPSession *child = new level::TCPSession();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}

	return (false);
}

bool AppSettings::BuildParser(level::TCPSession &parser, tinyxml2::XMLElement *container, const std::string &name) {
	if (name == "HTTP") {
		level::HTTP *child = new level::HTTP();
		parser.AddFollower(child->AsFollower());
		ParseParsers(*child, container);
		return (true);
	}

	return (false);
}

bool AppSettings::BuildParser(level::HTTP &parser, tinyxml2::XMLElement *container, const std::string &name) {
	return (false);
}

void AppSettings::ParseError(const std::string &msg)
{
	const std::string error = "cannot parse config file " + File + ": " + msg;
	ttop::utils::fatalError(error);
}

} /* namespace ttop */
