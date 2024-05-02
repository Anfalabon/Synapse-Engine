
#ifndef LOG_HPP
#define LOG_HPP

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

namespace DEBUG
{
#define LOG(x) std::clog << x << '\n'
#define LOG_GLM(x) std::clog << glm::to_string(x) << '\n'
#define SYSTEM_LOG(system_command) system(system_command)
}

#endif //LOG_HPP