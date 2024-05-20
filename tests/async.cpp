#include <iostream>
#include <future>
#include <mutex>
#include <chrono>
#include <thread>
#include <math.h>
#include <vector>
#include <omp.h>


std::size_t sumEvenSin(const std::size_t start, const std::size_t end)
{
    std::size_t sum = 0;
    for(std::size_t i=start; i<=end; ++i)
    {
        if(i%2 != 0)
        {
            sum += sin(i)*cos(i);
            //sum += i;
        }
    }
    return sum;
}



std::size_t sumOddSin(const std::size_t start, const std::size_t end)
{
    std::size_t sum = 0;
    for(std::size_t i=start; i<=end; ++i)
    {
        if(i%2 != 0)
        {
            sum += sin(i)*cos(i);
            //sum += i;
        }
    }
    return sum;
}



float accumulateSin(std::size_t i)
{
    return sin(i);
}


int main()
{

    std::size_t range = 900000000;

    float sum = 0.0f;

    std::vector<std::future<float>> futures;

    auto start = std::chrono::high_resolution_clock::now();

    omp_set_num_threads(6);
    #pragma omp parallel for
    for(std::size_t i=0; i<range; ++i)
    {
        sum += accumulateSin(i);
    }

    std::cout << sum << '\n';

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds." << '\n';


    return 0;
}