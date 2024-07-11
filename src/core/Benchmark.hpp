#pragma once

#include "core/Timer.hpp"
#include "core/Macros.hpp"


namespace Synapse
{



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


//#define S_START_BENCHMARKING() benchmarker.Start()
//#define S_END_BENCHMARKING() benchmarker.ShutDown()
//#define S_PRINT_BENCHMARKING_RESULT() benchmarker.PrintResult
//#define S_SHUTDOWN_BENCHMARKER() benchmarker = Synapse::Timer()


}