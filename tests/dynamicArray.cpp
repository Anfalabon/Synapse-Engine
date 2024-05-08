
#include "dynamicArray.hpp"


int main()
{
    Hilbert::DyArray<float> objects(3);

    objects.add(1.0f);
    objects.add(2.0f);
    objects.add(3.0f);

    objects.display();

    return 0;
}