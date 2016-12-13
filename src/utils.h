
#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <string>
#include <vector>
#include <functional>

namespace ttop {
namespace utils {

extern bool exitRequested;
extern std::vector<std::function<void(int)> > onExitHooks;
void requestExit(int code);

void fatalError (const std::string &msg);

std::string semiHexStr(const std::string &data, uint16_t maxlen);
bool isPrintable(const std::string &data);

}
}



#endif /* SRC_UTILS_H_ */
