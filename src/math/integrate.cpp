#include <iostream>
#include <functional>
#include <math.h>
#include <climits>
#include <type_traits>
#include <vector>


//will use Template Metaprogramming to calculate the integration at compile time.

#define PI 3.14159

namespace Hilbert
{

template<typename T> struct Function
{
public:
    Function(std::function<T(T)> function)
        : _function(function){}

    bool isEven()
    {
        T x;
        return _function((-1)*x)==_function(x);
    }

    void findRoots();
    void findDomain();
    void findRange();

private:
    std::function<T(T)> _function;
    std::vector<T> _roots;
    T _domain;
    T _range;

};

}


namespace Hilbert
{

//accuracy refers to the amount of rectangles created to approximate the area
template<typename T>
T integrate(std::function<T(T)> y,
            T lowerLimit,
            T upperLimit,
            std::size_t accuracy)
{
    if(!std::is_floating_point<T>::value)
    {
        std::clog << "Failed to integrate because of incorrect Type!" << '\n';
        return INT_MIN;
    }

    if(lowerLimit==upperLimit)
        return static_cast<T>(0.0f);

    T delX = (upperLimit-lowerLimit)/accuracy;
    T sum = 0;
    for (std::size_t i=1; i<=accuracy; ++i)
        sum += y(lowerLimit + i*delX);
    return sum*delX;
}

}


unsigned int factorial(unsigned int x)
{
    return x == 0 ? 1 : x * factorial(x - 1);
}



int main()
{
    auto function = [](float x)->float
    {
        return std::atan(x)/(1+((1+x*x)*(1+x*x)));
    };

    std::size_t accuracy = 10;
    float area = Hilbert::integrate<double>(factorial, 0.0f, 3.0f, accuracy);

    std::cout << "Area under the curve: " << area << " units." << '\n';


    return 0;
}