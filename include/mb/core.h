#ifndef LIBMB_CORE_H
#define LIBMB_CORE_H
#include "int.h"
#include "result.h"
#include <string>

namespace mb {

mb::result<std::string> getenv(const std::string &env_name);

}

#endif//LIBMB_CORE_H
