#pragma once

#include <iostream>

namespace Synapse
{

//#define S_PAUSE_FOR_READING() std::cin.get()

#define S_PAUSE_FOR_READING() std::cout << "In FILE: " << __FILE__ << ", FUNCTION: " << __func__ << ", LINE: " << __LINE__ << " ==> " \
                                            << "\e[32m" << "PAUSED FOR READING..." << "\e[0m" << '\n'; \
                                            std::cin.get()


#if defined(_MSC_VER)
    #define __ALWAYS__INLINE__ __forceinline
#elif defined(__linux__) || defined(__unix__)
    #define __ALWAYS__INLINE__ __attribute__((always_inline)) inline
#endif

#define __ALLOW_PACKING__ __attribute__((packing))
#define __declspecUnix() __attribute__((visibility("default")))
#define __DONT__DISCARD__ [[nodiscard]]
#define __DEFAULT__CAMERA__INDEX__ID__ 0x0


}

