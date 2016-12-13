// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include <iostream>
#include <tclap/CmdLine.h>
#include "consts.h"
#include "config.h"
#include "utils.h"
#include "AppSettings.h"
#include <TrafficAccounting/core/utils.h>
#include <pcap.h>
#include "ParserDescription.h"

#include <fcntl.h>
#include <unistd.h>
#include <pcap.h>

std::string ttop::config::parsersXmlFile;
std::string ttop::config::inputFile;


void parseCmdLine (int argc, char** argv)
{
	try {
		TCLAP::CmdLine cmd("ttop is top-like tool to monitor network traffic", ' ', ttop::consts::programVersion);

		TCLAP::ValueArg<std::string> parsersXml("c","config","Path to config file",false,"/etc/ttop/parsers.xml","file");

		TCLAP::ValueArg<std::string> inputFile("i","input","Path to input file (use '-' for STDIN, this is default) or use format iface:eth0 to gather data from specified interface",false,"-","file");

		TCLAP::SwitchArg helpParsers("p", "help-parsers", "Print available parsers and exit");

		cmd.add(parsersXml);
		cmd.add(inputFile);
		cmd.add(helpParsers);

		cmd.parse(argc, argv);

		if (helpParsers.getValue()) {
			std::string followers = ttop::parserDescription::generateAccepts(ttop::parserDescription::EtherNet);
			std::string descriptions = ttop::parserDescription::generateDescription(ttop::parserDescription::EtherNet);
			std::string help =
					"\n\n"
					"Each parser can have followers:\n\n"
					+ followers
					+ "\n\nDescription:\n\n"
					+ descriptions
					+ "\n";
			std::cout << help << std::endl;
			exit (0);
		}

		ttop::config::parsersXmlFile = parsersXml.getValue();
		ttop::config::inputFile = inputFile.getValue();
	} catch (TCLAP::ArgException &e) {
		const std::string msg = e.error() + "for arg " + e.argId();
		ttop::utils::fatalError(msg);
	}
}

static const std::string iface_prefix = "iface:";

void processPcapIface (ttop::AppSettings settings) {
	std::string device = ttop::config::inputFile.substr(iface_prefix.size());

	char errbuf[PCAP_ERRBUF_SIZE];

	pcap_if_t *interfaces;

	if(pcap_findalldevs(&interfaces, errbuf) == -1)
		ttop::utils::fatalError("Cannot get list of interfaces: " + std::string(errbuf));

	pcap_if_t *iface;
	bool deviceFound = false;
	for (iface = interfaces; iface; iface = iface->next) {
		if (device == iface->name) {
			deviceFound = true;
			break;
		}
	}

	if (!deviceFound)
		ttop::utils::fatalError("Cannot find device: " + device);

	pcap_t *pcap_handler = pcap_open_live(device.c_str(), 65535, 1, 0, errbuf);
	if (!pcap_handler)
		ttop::utils::fatalError("Cannot open device: " + device);

	bool done = false;
	while (!done) {
		try {
			auto InputData = util::quiltOfPcapHandler(pcap_handler);
			settings.Parser.Recursive(InputData);
		} catch (std::exception &exn) {
			done = true;
		}
	}

	pcap_close(pcap_handler);
}

void processFile (ttop::AppSettings settings) {
	int FD = 0;

	if (ttop::config::inputFile != "-")
		FD = open(ttop::config::inputFile.c_str(), 0);

	util::skipBytesInFD(FD, sizeof (pcap_file_header));
	bool done = false;
	while (!done) {
		try {
			auto InputData = util::quiltOfPcap(FD);
			settings.Parser.Recursive(InputData);
		} catch (std::exception &exn) {
			done = true;
		}
	}
}

int main (int argc, char** argv)
{
	parseCmdLine(argc, argv);
	ttop::AppSettings settings(ttop::config::parsersXmlFile);

	if (!ttop::config::inputFile.compare(0, iface_prefix.size(), iface_prefix)) {
		processPcapIface(settings);
	} else {
		processFile(settings);
	}

	ttop::utils::requestExit(0);
	return (0);
}
