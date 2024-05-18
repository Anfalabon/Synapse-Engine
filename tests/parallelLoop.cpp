

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <random>
#include <chrono>
#include <thread>

//#include <omp.h>


int main()
{
    std::size_t range = 1000000000;
    std::vector<std::uint64_t> v;
    v.reserve(range);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

    for(std::size_t i=0; i<range; ++i)
        v.push_back(dist6(rng));

    std::cout << "Finised setting up." << '\n';

    std::size_t sum = 0;
    auto partialSum = [range, &sum, &v](std::size_t first, std::size_t last)->void
    {
        for(std::size_t i=first; i<last; ++i)
        {
            sum += sin(v[i]);
        }
    };

#define TOTAL_THREADS 16

    std::vector<std::thread> sumThreads;
    sumThreads.reserve(TOTAL_THREADS);



    for(std::size_t i=0; i<TOTAL_THREADS; ++i)
    {
        auto f = (i*range)/TOTAL_THREADS;
        auto l = ((i+1)*range)/TOTAL_THREADS;

        sumThreads.push_back(std::thread(partialSum, f, l));
    }



    auto start = std::chrono::high_resolution_clock::now();

    for(std::size_t i=0; i<TOTAL_THREADS; ++i)
    {
        sumThreads[i].join();
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds." << '\n';
    std::cout << "Total sum: " << sum << '\n';

    return 0;
}

