#pragma once

#include <iostream>

namespace Synapse
{

#define S_PAUSE_FOR_READING() std::cin.get()

#if defined(_MSC_VER)
    #define __ALWAYS__INLINE__ __forceinline
#elif defined(__linux__) || defined(__unix__)
    #define __ALWAYS__INLINE__ __attribute__((always_inline)) inline
#endif

#define __ALLOW_PACKING__ __attribute__((packing))
#define __declspecUnix() __attribute__((visibility("default")))
#define __DONOT__NEGLECT__RETURN__VALUE__ [[nodiscard]]

}

