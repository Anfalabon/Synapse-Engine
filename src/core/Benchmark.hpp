#pragma once

#include "core/Timer.hpp"
#include "core/Macros.hpp"

#include <stdio.h>
#include <functional>


namespace Synapse
{


class Benchmark
{
public:
//    static void S_START_BENCHMARKING();
//    static void S_END_BENCHMARKING();
//    static void S_PRINT_BENCHMARKING_RESULT();
//    static void S_SHUTDOWN_BENCHMARKER();

    template<typename RETURN_TYPE, typename PARAMETER_TYPE>
    static __ALWAYS__INLINE__ void S_BENCHMARK(const std::function<RETURN_TYPE(PARAMETER_TYPE)> &codeBlock)
    {
        Synapse::Timer benchmark;
        benchmark.Start();
        codeBlock;
        benchmark.ShutDown();
        benchmark.PrintResult();
    }

private:
    //std::uint64_t m_benchmarkingData;
};


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