#include "Benchmark.hpp"

namespace Synapse
{



Synapse::Timer benchmarker = Synapse::Timer();

void S_START_BENCHMARKING()
{
    benchmarker.Start();
}

void S_END_BENCHMARKING()
{
    benchmarker.ShutDown();
}

void S_PRINT_BENCHMARKING_RESULT()
{
    benchmarker.PrintResult();
}

void S_SHUTDOWN_BENCHMARKER()
{
    benchmarker = Synapse::Timer();
}


//void S_BENCHMARK(void (*block)(void))
//{
//    S_START_BENCHMARKING();
//    block();
//    S_END_BENCHMARKING();
//    S_PRINT_BENCHMARKING_RESULT();
//    S_SHUTDOWN_BENCHMARKER();
//}



}
