//
// Created by anfal on 5/8/24.
//

#ifndef SIMULATION_DYNAMICARRAY_H
#define SIMULATION_DYNAMICARRAY_H

#include <iostream>

namespace Hilbert
{

#define __MAX_MEMORY_ALLOC_LIMIT__ 10000000
    template <class T> class DyArray
    {
    public:

        DyArray() = default;
        DyArray(std::size_t dataSize)
                : _dataSize(dataSize)
        {
            if(_dataSize >= __MAX_MEMORY_ALLOC_LIMIT__)
            {
                std::clog << "Allocation failed!" << '\n';
                return;
            }

            if(_data == nullptr)
                _data = new T[_dataSize];

            for(std::size_t i=0; i<_dataSize; ++i)
                _data[i] = 0;
        }

        ~DyArray()
        {
            delete[] _data;
        }


        void add(T element)
        {
            if(_data != nullptr)
            {
                (_data+_dataSize) = new T(element);
                ++_dataSize;
            }
        }

        void remove()
        {
            if(_data != nullptr)
                (_data+_dataSize-1) = nullptr;

        }

        void display()
        {
            for(std::size_t i=0; i<_dataSize; ++i)
                std::cout << _data[i] << '\n';

        }

        T &operator[](std::size_t index)
        {
            return _data[index];
        }

    private:
        T *_data = nullptr;
        std::size_t _dataSize = 0;
    };
}



int main()
{
    Hilbert::DyArray<float> objects(3);

    objects.add(1.0f);
    objects.add(2.0f);
    objects.add(3.0f);

    objects.display();

    return 0;
}



#endif //SIMULATION_DYNAMICARRAY_H
