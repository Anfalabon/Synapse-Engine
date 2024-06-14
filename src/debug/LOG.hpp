#pragma once

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


namespace Synapse
{

#define __DEBUG__
#ifdef __DEBUG__

namespace DEBUG
{
struct __LOG__MANAGER__
{
//#define LOG(__log__txt__) std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << __log__txt__ << '\n'

    inline static void LOG(){}
    template<typename T, typename... Args> inline static void LOG(T __log__txt__, Args ... args) __attribute__((always_inline))
    {
        std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << __log__txt__ << '\n';
        LOG(args...);
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

//#define LOG(log_message) LOG(log_message, __FILE__, __func__, __LINE__)
//#define LOG(_log_message_) std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << _log_message_ << '\n'


};



}

#endif

//#ifdef __DEBUG__
//    #undef __DEBUG__
//#endif


}


