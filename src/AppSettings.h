
#ifndef SRC_APPSETTINGS_H_
#define SRC_APPSETTINGS_H_

#include <string>
#include <tinyxml2.h>

#include "levels/EtherNet.h"
#include "levels/EtherNetDIX.h"
#include "levels/EtherNetRAW.h"
#include "levels/EtherNetSNAP.h"
#include "levels/EtherNet802LLC.h"
#include "levels/IPv4.h"
#include "levels/IPv6.h"
#include "levels/IPv4Packet.h"
#include "levels/TCP.h"
#include "levels/UDP.h"
#include "levels/TCPSession.h"
#include "levels/HTTP.h"

namespace ttop {

class AppSettings {
public:
	AppSettings(std::string &file);
	void Load();

	std::string ExpectedRootElementName = "ttop";
	std::string File;
	level::EtherNet Parser;

private:
	void ParseError(const std::string &msg);

	template <typename PARENT>
	void ParseParsers(PARENT &parent, tinyxml2::XMLElement *parsers);

	bool BuildParser(level::EtherNet &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::EtherNetDIX &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::EtherNetRAW &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::EtherNet802LLC &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::EtherNetSNAP &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::IPv4 &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::IPv4Packet &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::IPv6 &parser, tinyxml2::XMLElement *container, const std::string &name);

	bool BuildParser(level::UDP &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::TCP &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::TCPSession &parser, tinyxml2::XMLElement *container, const std::string &name);
	bool BuildParser(level::HTTP &parser, tinyxml2::XMLElement *container, const std::string &name);
};

} /* namespace ttop */

#endif /* SRC_APPSETTINGS_H_ */
