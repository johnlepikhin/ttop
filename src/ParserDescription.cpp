/*
 * ParseTreeBuilder.cpp
 *
 *  Created on: 25 окт. 2016 г.
 *      Author: eugene
 */

#include "ParserDescription.h"

namespace ttop {
namespace parserDescription {

info UDP = {
		.id = "UDP",
		.description = "UDP datagram",
		.children = {}
};

info TCPSession = {
		.id = "TCPSession",
		.description = "TCP sessions",
		.children = {}
};

info TCP = {
		.id = "TCPChunk",
		.description = "TCP chunk",
		.children = { TCPSession }
};

info IPv4Packet = 						{
		.id = "IPv4Packet",
		.description = "IPv4 packet",
		.children = {
				TCP,
				UDP
		}
};

info IPv4 = {
		.id = "IPv4",
		.description = "IPv4 chunk",
		.children = { IPv4Packet }
};

info IPv6 = {
		.id = "IPv6",
		.description = "IPv6 chunk",
		.children = { }
};

info EtherNetDIX = {
		.id = "DIX",
		.description = "Ethernet DIX frame",
		.children = { IPv4, IPv6 }
};

info EtherNetRAW = {
		.id = "RAW",
		.description = "Ethernet RAW frame",
		.children = { }
};

info EtherNet802LLC = {
		.id = "802LLC",
		.description = "Ethernet 802.11 LLC frame",
		.children = { }
};

info EtherNetSNAP = {
		.id = "SNAP",
		.description = "Ethernet SNAP frame",
		.children = { }
};

info EtherNet = {
		.id = "Ethernet",
		.description = "Main Ethernet parser",
		.children = { EtherNetDIX, EtherNetRAW, EtherNet802LLC, EtherNetSNAP }
};

std::string generateAccepts(info &root)
{
	std::string r = root.id + ": ";
	if (root.children.size()) {
		for (auto c : root.children) {
			r += " " + c.id;
		}
	} else {
		r += " <none>";
	}
	r += "\n";
	for (auto c : root.children) {
		r += generateAccepts(c);
	}

	return (r);
}

std::string generateDescription(info &root)
{
	std::string r = root.id + ": " + root.description + "\n";
	for (auto c : root.children) {
		r += generateDescription(c);
	}

	return (r);
}

}

} /* namespace ttop */