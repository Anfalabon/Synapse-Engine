#pragma once

#include "core/Macros.hpp"

#include <iostream>
#include <stdio.h>
#include <assert.h>


namespace Synapse
{

#define FAILED 0
#define S_ASSERT(X) assert(X)
//#define S_CORE_INITIALIZATION_ASSERT(X) assert(X)


__ALWAYS__INLINE__ static void S_CORE_INITIALIZATION_ASSERT(bool __INITALIZE__LOG__, const char *__ASSERT__MESSAGE__)
{
    assert(__INITALIZE__LOG__!=FAILED && __ASSERT__MESSAGE__);
}


template<typename T>
__ALWAYS__INLINE__ static void S_NULL_ASSERT(T *ptr, const char *__ASSERT__MESSAGE__)
{
    assert(ptr!=nullptr && __ASSERT__MESSAGE__);
}


template<typename T>
__ALWAYS__INLINE__ static void S_GREATER_THAN_ZERO_ASSERT(T value)
{
    assert(value>0);
}



}



