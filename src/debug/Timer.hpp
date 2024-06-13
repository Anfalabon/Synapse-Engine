#pragma once

#include <chrono>
#include <thread>

namespace Synapse
{

struct Timer
{
public:

    Timer() = default;
    ~Timer() = default;

    void Start();
    void ShutDown();
    void PrintResult();

private:
    std::chrono::time_point <std::chrono::high_resolution_clock> start;
    std::chrono::time_point <std::chrono::high_resolution_clock> end;
    std::chrono::duration<double> duration;
};

}