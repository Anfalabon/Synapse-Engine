#include <iostream>

extern "C"{
    int add(int x, int y);
}

int main(int argc, char **argv)
{
    std::cout << add(1, 2) << '\n';
    return 0;
}