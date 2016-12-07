
#ifndef SRC_PARSERDESCRIPTION_H_
#define SRC_PARSERDESCRIPTION_H_

#include <levels/ParserChunkSSL.h>
#include <levels/ParserHTTP.h>
#include <levels/ParserPacketMySQL.h>
#include <TrafficAccounting/levels/ParserEtherNet.h>
#include <TrafficAccounting/levels/ParserEtherNetDIX.h>
#include <TrafficAccounting/levels/ParserEtherNetRAW.h>
#include <TrafficAccounting/levels/ParserEtherNet802LLC.h>
#include <TrafficAccounting/levels/ParserEtherNetSNAP.h>

#include <TrafficAccounting/levels/ParserIPv4.h>
#include <TrafficAccounting/levels/ParserIPv6.h>

#include <TrafficAccounting/levels/ParserPacketIPv4.h>
#include <TrafficAccounting/levels/ParserTCP.h>
#include <TrafficAccounting/levels/ParserSessionTCP.h>
#include <TrafficAccounting/levels/ParserUDP.h>
#include <tinyxml2.h>
#include <map>

namespace ttop {
namespace parserDescription {

struct Description {
	const std::string id;
	const std::string description;
	const std::vector<Description> children;
};

typedef struct Description info;

extern info SSL;

extern info MySQL;

extern info HTTP;

extern info TCPSession;

extern info TCP;

extern info IPv4Packet;

extern info IPv4;

extern info IPv6;

extern info UDP;

extern info TCP;

extern info EtherNetDIX;

extern info EtherNetRAW;

extern info EtherNetSNAP;

extern info EtherNet802LLC;

extern info EtherNet;

std::string generateAccepts(const info &root);
std::string generateDescription(const info &root);

}

} /* namespace ttop */

#endif /* SRC_PARSERDESCRIPTION_H_ */
