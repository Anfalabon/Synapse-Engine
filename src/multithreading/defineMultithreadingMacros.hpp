#pragma once

#if defined(__RELEASE__)
    #define __RUNTIME__MULTITHREADING__
    //#define __LOADTIME__MULTITHREADING__
#elif defined(__DEBUG__)
#define __SINGLETHREADING__
#endif

