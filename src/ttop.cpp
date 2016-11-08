

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

std::string ttop::config::parsersXmlFile;

void parseCmdLine (int argc, char** argv)
{
	try {
		TCLAP::CmdLine cmd("ttop is top-like tool to monitor network traffic", ' ', ttop::consts::programVersion);

		TCLAP::ValueArg<std::string> parsersXml("c","config","Path to config file",false,"/etc/ttop/parsers.xml","file");

		TCLAP::SwitchArg helpParsers("p", "help-parsers", "Print available parsers and exit");

		cmd.add(parsersXml);
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
	} catch (TCLAP::ArgException &e) {
		const std::string msg = e.error() + "for arg " + e.argId();
		ttop::utils::fatalError(msg);
	}
}


int main (int argc, char** argv)
{
	parseCmdLine(argc, argv);
	ttop::AppSettings settings(ttop::config::parsersXmlFile);

	// TMP
	bool done = false;
	int FD = open("/home/eugene/workspace/TrafficAccounting/dumps/dump-l28", 0);
	util::skipBytesInFD(FD, sizeof (pcap_file_header));
	while (!done) {
		try {
			auto InputData = util::quiltOfPcap(FD);
			settings.Parser.Recursive(InputData);
		} catch (std::exception &exn) {
			done = true;
		}
	}

	return (0);
}
