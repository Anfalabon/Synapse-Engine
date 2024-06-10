#include "../src/debug/LOG.hpp"
#include "../src/debug/Timer.hpp"

#include <stdio.h>
#include <array>
#include <vector>



constexpr std::size_t size = 1000000000;
float a = 3.14f;
int b;


inline void reinterpret(){b = *(int*)&a;}
inline void bracesAroundType(){b = (int)a;}
inline void bracesAroundData(){b = int(a);}
inline void cppStaticCast(){b = static_cast<int>(a);}

//int (*p[4]) (int x, int y);


void (*q[4]) ();


q[0] = reinterpret;
q[1] = bracesAroundType;
q[2] = bracesAroundData;
q[3] = cppStaticCast;




int main()
{


    Synapse::DEBUG::__LOG__MANAGER__::LOG("b before casting: ");
    Synapse::DEBUG::__LOG__MANAGER__::LOG(b);


    std::array<Synapse::Timer, 4> timers;


    Synapse::DEBUG::__LOG__MANAGER__::LOG("b after casting: ");
    Synapse::DEBUG::__LOG__MANAGER__::LOG(b);



    for(std::size_t j=0; j<4; ++j)
    {
        timers[i].Start();
        for(std::size_t i=0; i<size; ++i)
        {
            q[i];
        }
        timers[i].ShutDown();
    }

    for(std::size_t i=0; i<4; ++i)
    {
        timers[i].PrintResult("Total time taken for casting: ");
    }





    return 0;
}