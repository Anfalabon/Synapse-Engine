#include <iostream>

//#define HAPPY_ENDING
//#define BAD_ENDING

int main()
{

    float value = 9.3742984576294576238574f;

    double reinterpret = *(double*)&value;

    std::cout << reinterpret << '\n';


#if defined(HAPPY_ENDING)
    std::cout << "Hello world!" << '\n';
#elif defined(BAD_ENDING)
    std::cout << "Bye world!" << '\n';
#endif

    return 0;
}