// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "utils.h"
#include <iostream>
#include <stdlib.h>

namespace ttop {
namespace utils {

std::vector<std::function<void(int)> > onExitHooks;

bool exitRequested = false;

void requestExit(int code) {
	exitRequested = true;
	for (auto fn : onExitHooks) {
		fn(code);
	}

	exit(code);
}

void fatalError (const std::string &msg)
{
	std::cerr << "Error: " << msg << std::endl;
	exit (EXIT_FAILURE);
}

constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

std::string semiHexStr(const std::string &data, uint16_t maxlen)
{
	std::string s;
	s.reserve(maxlen);
	size_t pos = 0;
	for (size_t i = 0; i < data.length(); ++i) {
		if (data[i] < 32 || data[i] > 126) { //-V112
			if (pos+3 > maxlen)
				return (s);
			s.resize(s.length()+3);
			s[pos] = hexmap[(data[i] & 0xF0) >> 4];
			s[pos+1] = hexmap[data[i] & 0x0F];
			s[pos+2] = ' ';
			pos+=3;
		} else {
			if (pos+1 > maxlen)
				return (s);
			s.resize(s.length()+1);
			s[pos]=data[i];
			pos++;
		}
	}
	return (s);
}

bool isPrintable(const std::string &data)
{
	for (size_t i = 0; i < data.length(); ++i) {
		if (data[i] < 32 || data[i] > 126) //-V112
			return (false);
	}
	return (true);
}

}
}


