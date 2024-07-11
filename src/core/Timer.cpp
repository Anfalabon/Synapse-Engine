#include "Timer.hpp"

#include <iostream>


namespace Synapse
{

void Timer::Start()
{
    start = std::chrono::high_resolution_clock::now();
}

void Timer::ShutDown()
{
    end = std::chrono::high_resolution_clock::now();
}

void Timer::PrintResult()
{
    duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds." << '\n';
}


}


