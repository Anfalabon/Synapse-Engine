#pragma once



#if  defined(__RUNTIME__MULTITHREADING__) || defined(__LOADTIME__MULTITHREADING__)

#include <thread>
#include <omp.h>
#include <algorithm>    //std::execution::policy in std::for_each()
#include <execution>

#endif


namespace Synapse
{

class ThreadPools
{
public:
    ThreadPools() = default;
    ~ThreadPools() = default;
private:

};

}