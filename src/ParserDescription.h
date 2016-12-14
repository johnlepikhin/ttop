
#ifndef SRC_PARSERDESCRIPTION_H_
#define SRC_PARSERDESCRIPTION_H_

#include "levels/ParserChunkSSL.h"
#include "levels/ParserHTTP.h"
#include "levels/ParserPacketMySQL.h"
#include "levels/ParserEtherNet.h"
#include "levels/ParserEtherNetDIX.h"
#include "levels/ParserEtherNetRAW.h"
#include "levels/ParserEtherNet802LLC.h"
#include "levels/ParserEtherNetSNAP.h"

#include "levels/ParserIPv4.h"
#include "levels/ParserIPv6.h"

#include "levels/ParserPacketIPv4.h"
#include "levels/ParserTCP.h"
#include "levels/ParserSessionTCP.h"
#include "levels/ParserUDP.h"
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

extern info EtherNetTraits;

extern info EtherNetRAW;

extern info EtherNetSNAP;

extern info EtherNet802LLC;

extern info EtherNet;

std::string generateAccepts(const info &root);
std::string generateDescription(const info &root);

}

} /* namespace ttop */

#endif /* SRC_PARSERDESCRIPTION_H_ */
