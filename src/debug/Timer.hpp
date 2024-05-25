#pragma once

#include <chrono>
#include <thread>

struct Timer
{
public:

    Timer() = default;
    ~Timer() = default;

    void Start()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    void ShutDown()
    {
        end =  std::chrono::high_resolution_clock::now();
    }

    void PrintResult(const std::string &message)
    {
        duration = end - start;
        std::cout << message << '\n';
        std::cout << "Time taken: "<< duration.count() << " seconds." << '\n';
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::duration<double> duration;
};

