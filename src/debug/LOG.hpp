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
    template<typename T> inline static void LOG(T __log__txt__) __attribute__((always_inline))
    {
        std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << __log__txt__ << '\n';
    }
    template<typename T> inline static void GLM_LOG(T __glm__func__) __attribute__((always_inline))
    {
        std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << glm::to_string(__glm__func__) << '\n';
    }
    template<typename T> inline static void SYSTEM_LOG(T __system__cmd__) __attribute__((always_inline))
    {
        std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << '\n';
        system(__system__cmd__);
    }
};
}

}


