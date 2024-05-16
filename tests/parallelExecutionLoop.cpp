//
//
//#include <algorithm>
//#include <chrono>
//#include <cstdint>
//#include <iostream>
//#include <random>
//#include <vector>
//
//#define PARALLEL
//#ifdef PARALLEL
//#include <execution>
//    namespace execution = std::execution;
//#else
//enum class execution { seq, unseq, par_unseq, par };
//#endif
//
//void measure([[maybe_unused]] auto policy, std::vector<std::uint64_t> v)
//{
//    const auto start = std::chrono::high_resolution_clock::now();
//#ifdef PARALLEL
//    std::for_each(policy, v.begin(), v.end(), [](std::size_t element)->void
//    {
//        double tan = sin(element)/cos(element);
//    });
//#else
//    std::for_each(policy, v.begin(), v.end(), [](std::size_t element)->void
//    {
//        double tan = sin(element)/cos(element);
//    });
//#endif
//    const auto end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> duration = end - start;
//    std::cout << duration.count() << " seconds." << '\n';
//};
//
//
//
//
//
//
//
//int main()
//{
//    std::vector<std::uint64_t> v;
//    v.reserve(900000000);
//    std::mt19937 gen{std::random_device{}()};
//    std::ranges::generate(v, gen);
//
//    measure(execution::seq, v);
//    measure(execution::unseq, v);
//    measure(execution::par_unseq, v);
//    measure(execution::par, v);
//}
//
//
//
//




#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
#include <execution>
#include <thread>


void process1(int value)
{
    std::cout << "Processing1 value: " << value << std::endl;
}

void process2(int value)
{
    std::cout << "Processing2 value: " << value << std::endl;
}

void process3(int value)
{
    std::cout << "Processing3 value: " << value << std::endl;
}

void process4(int value)
{
    std::cout << "Processing4 value: " << value << std::endl;
}

void process5(int value)
{
    std::cout << "Processing5 value: " << value << std::endl;
}

void process6(int value)
{
    std::cout << "Processing6 value: " << value << std::endl;
}



int main()
{
    auto range = 10;
    std::vector<std::uint64_t> v;
    v.reserve(range);
    for(std::size_t i=0; i<range; ++i)
        v.push_back(i);


    std::vector<std::thread> threads;


    // Execute process() function in parallel using std::execution::par
    std::for_each(std::execution::par, v.begin(), v.end(), [&threads](int value)
    {
//        process1(value);
//        process2(value);
//        process3(value);
//        process4(value);
//        process5(value);
//        process6(value);

        threads.push_back(std::thread(process1, value));
        threads.push_back(std::thread(process2, value));
        threads.push_back(std::thread(process3, value));
        threads.push_back(std::thread(process4, value));
        threads.push_back(std::thread(process5, value));
        threads.push_back(std::thread(process6, value));
    });

    return 0;
}

