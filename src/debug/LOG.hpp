#pragma once

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


namespace Synapse
{

namespace DEBUG
{
struct __LOG__MANAGER__
{
    template<typename T> inline static void LOG(T __log__txt__) { std::clog << __log__txt__ << '\n'; }
    template<typename T> inline static void GLM_LOG(T __glm__func__) { std::clog << glm::to_string(__glm__func__) << '\n'; }
    template<typename T> inline static void SYSTEM_LOG(T __system__cmd__) { system(__system__cmd__); }
};
}

}


