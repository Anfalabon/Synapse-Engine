#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <array>
#include <vector>
#include <algorithm>




std::size_t sumEvenSin(const std::size_t start, const std::size_t end)
{
    std::size_t sum = 0;
    for(std::size_t i=start; i<=end; ++i)
    {
        if(i%2 != 0)
        {
            sum += sin(i);
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
            sum += sin(i);
            //sum += i;
        }
    }
    return sum;
}


int main()
{
    std::size_t range = 900000000;
    auto start =std::chrono::high_resolution_clock::now();


//    sumEvenSin(range);
//    sumOddSin(range);

//    std::thread firstThread(sumEvenSin, 0, range/2);
//    std::thread secondThread(sumEvenSin, range/2, range);
//    std::thread thirdThread(sumOddSin, 0, range/2);
//    std::thread fourthThread(sumOddSin, range/2, range);
//
//    firstThread.join();
//    secondThread.join();
//    thirdThread.join();
//    fourthThread.join();


    std::thread firstThread(sumEvenSin, 0, range/4);
    std::thread secondThread(sumEvenSin, range/4, range/2);
    std::thread thirdThread(sumEvenSin, range/2, (3*range)/4);
    std::thread fourthThread(sumEvenSin, (3*range)/4 , range);

    std::thread fifthThread(sumOddSin, 0, range/4);
    std::thread sixthThread(sumOddSin, range/4, range/2);
    std::thread seventhThread(sumOddSin, range/2, (3*range)/4);
    std::thread eightThread(sumOddSin, (3*range)/4 , range);

    firstThread.join();
    secondThread.join();
    thirdThread.join();
    fourthThread.join();

    fifthThread.join();
    sixthThread.join();
    seventhThread.join();
    eightThread.join();





    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;


    std::cout << "Execution time: " << duration.count() << " seconds." << '\n';

    return 0;
}
