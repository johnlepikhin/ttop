// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "utils.h"
#include <iostream>
#include <stdlib.h>

namespace ttop {
namespace utils {

void fatalError (const std::string &msg)
{
	std::cerr << "Error: " << msg << std::endl;
	exit (EXIT_FAILURE);
}

}
}


