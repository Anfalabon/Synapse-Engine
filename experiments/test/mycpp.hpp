#pragma once

#include <math.h>
#include <type_traits>



namespace Synapse
{


typedef struct Mathmatica
{
public:

    Mathmatica(){}
    ~Mathmatica() = default;


    template<typename T> inline static auto add(const T &a, const T &b)->T
    {
        return (a + b);
    }


private:

    const double pi = 3.14159f;

}Math;


}
