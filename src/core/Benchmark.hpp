#pragma once

#include "core/Timer.hpp"
#include "core/Macros.hpp"

#include <stdio.h>


namespace Synapse
{


#if 0

Synapse::Timer benchmarker;

__ALWAYS__INLINE__ void S_START_BENCHMARKING()
{
    benchmarker.Start();
}

__ALWAYS__INLINE__ void S_END_BENCHMARKING()
{
    benchmarker.ShutDown();
}

__ALWAYS__INLINE__ void S_PRINT_BENCHMARKING_RESULT()
{
    benchmarker.PrintResult();
}

__ALWAYS__INLINE__ void S_SHUTDOWN_BENCHMARKER()
{
    benchmarker = Synapse::Timer();
}
#else

extern Synapse::Timer benchmarker;
extern void S_START_BENCHMARKING();
extern void S_END_BENCHMARKING();
extern void S_PRINT_BENCHMARKING_RESULT();
extern void S_SHUTDOWN_BENCHMARKER();
//extern void S_BENCHMARK(void (*block)(void));




//#define S_BENCHMARK(codeBlock) do { \
//        S_START_BENCHMARKING();     \
//        codeBlock;                  \
//        S_END_BENCHMARKING();       \
//        S_PRINT_BENCHMARKING_RESULT(); \
//        S_SHUTDOWN_BENCHMARKER();   \
//}while(0);











#define S_BENCHMARK(codeBlock)      \
                                    \
        S_START_BENCHMARKING();     \
        codeBlock;                  \
        S_END_BENCHMARKING();       \
        S_PRINT_BENCHMARKING_RESULT(); \
        S_SHUTDOWN_BENCHMARKER();   \



//__ALWAYS__INLINE__ void S_BENCHMARK(void (*codeBlock)(void))
//{
//    S_START_BENCHMARKING();
//    codeBlock;
//    S_END_BENCHMARKING();
//    S_PRINT_BENCHMARKING_RESULT();
//    S_SHUTDOWN_BENCHMARKER();
//}



#endif

//#define S_START_BENCHMARKING() benchmarker.Start()
//#define S_END_BENCHMARKING() benchmarker.ShutDown()
//#define S_PRINT_BENCHMARKING_RESULT() benchmarker.PrintResult
//#define S_SHUTDOWN_BENCHMARKER() benchmarker = Synapse::Timer()


}