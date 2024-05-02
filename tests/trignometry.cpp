

#include <iostream>
#include <math.h>
#include <glm/glm.hpp>

constexpr float PI = 3.14159;

namespace iv
{
float sin(float x)
{
    bool isPositive = false;
    if(x > 0)
    {
        isPositive = true;
    }

    int t = static_cast<int>(x);
    t %= 180;
    x = static_cast<float>(t);
    //x *= PI/180.0f;
    x = glm::radians(x);
    return isPositive ? 0.4*x*(PI-x) : (-1.0f)*0.4*x*(x-PI);
}
}



int main()
{
    float i = 0.0f;
    while(i >= -360.0f)
    {
        std::clog << "iv::sin(" << i << ") : " << iv::sin(i) << '\n';
        std::clog << "glm::sin(" << i << ") : " << glm::sin(glm::degrees(i)) << '\n';
        std::clog << '\n';
        --i;

        std::cin.get();
    }
    return 0;
}





































