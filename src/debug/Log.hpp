#pragma once

#include "core/Macros.hpp"

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <stdio.h>


namespace Synapse
{


#define __DEBUG__
//#define __debug__
#ifdef __DEBUG__
    #define DEBUG(__debug__message__) std::cout << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " ==> " \
                                            << "\e[31m" << __debug__message__ << "\e[0m" << '\n'

    #define DEBUG_V(__value__) std::cout << __value__ << '\n';

    #define DEBUG_LOG(__expression__) printf(__expression__)
#else
    #define DEBUG(__debug__message__)
    #define DEBUG_V(__value__)
    #define DEBUG_LOG(__expression__)
#endif




namespace DEBUG
{


struct __LOG__MANAGER__
{

#ifdef __DEBUG__
    inline static void LOG(){}
    template<typename T, typename... Args> __ALWAYS__INLINE__ static void LOG(T __log__txt__, Args ... args)
    {
        std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << __log__txt__ << '\n';
        LOG(args...);
    }

    template<typename T> __ALWAYS__INLINE__ static void GLM_LOG(T __glm__func__)
    {
        std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << glm::to_string(__glm__func__) << '\n';
    }

    template<typename T> __ALWAYS__INLINE__ static void SYSTEM_LOG(T __system__cmd__)
    {
        std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << '\n';
        system(__system__cmd__);
    }

//#define LOG(log_message) LOG(log_message, __FILE__, __func__, __LINE__)
//#define LOG(_log_message_) std::clog << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " " << _log_message_ << '\n'

#else

    template<typename T, typename... Args> inline static void LOG(T __log__txt__, Args ... args){}
    template<typename T> inline static void GLM_LOG(T __glm__func__){}
    template<typename T> inline static void SYSTEM_LOG(T __system__cmd__){}

#endif



};



}

//#endif

//#ifdef __DEBUG__
//    #undef __DEBUG__
//#endif


}


