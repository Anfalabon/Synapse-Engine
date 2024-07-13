//#include "test.h"


extern "C"{
    int add(int x, int y);
}

#include <iostream>

int main()
{
    int sum = add(1, 2);

    std::cout << sum << '\n';

    return 0;
}