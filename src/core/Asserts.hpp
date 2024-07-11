#pragma once

#include <iostream>
#include <stdio.h>
#include <assert.h>
#define FAILED 0
#define S_ASSERT(X) assert(X)
//#define S_CORE_INITIALIZATION_ASSERT(X) assert(X)

//will create and bring all of the custom macros for 'Synapse' Engine in other directory
static void S_CORE_INITIALIZATION_ASSERT(bool __INITALIZE__LOG__, const char *__ASSERT__MESSAGE__)
{
    assert(__INITALIZE__LOG__!=FAILED && __ASSERT__MESSAGE__);
}

template<typename T>
static void S_NULL_ASSERT(T *ptr, const char *__ASSERT__MESSAGE__)
{
    assert(ptr!=nullptr && __ASSERT__MESSAGE__);
}
