
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


