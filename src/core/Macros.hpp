#pragma once

#include <iostream>

namespace Synapse
{

#define S_PAUSE_FOR_READING() std::cin.get()
#define __ALWAYS__INLINE__ __attribute__((always_inline)) inline
#define __ALLOW_PACKING__ __attribute__((packing))
#define __declspecUnix() __attribute__((visibility("default")))

}