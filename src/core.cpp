#include <cstdlib>
#include <mb/core.h>
#include <sstream>

namespace mb {

mb::result<std::string> getenv(const std::string &env_name) {
    auto value = std::getenv(env_name.c_str());
    if (value == nullptr) {
        std::stringstream ss;
        ss << "required environment variable not provided: ";
        ss << env_name;
        return mb::error(ss.str());
    }
    return std::string(value);
}

}// namespace mb