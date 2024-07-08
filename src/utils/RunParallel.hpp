#pragma once

#include <iostream>
#include <functional>
#include <thread>
#include <omp.h>
#include <mutex>
#include <assert.h>
#include <future>

//will solve serious issuses like Data Races, Race Conditions
namespace Synapse
{

struct Threading
{
    //let's create an custom for loop thread
    template<typename RETURN_TYPE, typename ITERATOR_TYPE>
    static void S_pragma_omp_parallel_loop(ITERATOR_TYPE __first, ITERATOR_TYPE __end, unsigned short __threads_num,
                                           std::function<RETURN_TYPE(ITERATOR_TYPE)> __func) {
        assert(__threads_num>0);
        omp_set_num_threads(__threads_num);
        #pragma omp parallel for
        for(ITERATOR_TYPE iterator=__first; iterator<__end; ++iterator)
            __func(iterator);
    }
};

}


////For instance it works like this
inline void compute_in_parallel()
{
    uint64_t sum = 0;
    unsigned short threadsToUtilize = 0x4;
    Synapse::Threading::S_pragma_omp_parallel_loop<void, int64_t>(1, 11, threadsToUtilize, [&sum](auto i)->void
    {
        sum += i;
    });

    //right now the answer will be definately wrong cause we haven't solved issuses like Data Races, Race Conditions
    std::cout << "Total sum: " << sum << '\n';
}



