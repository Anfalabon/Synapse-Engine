#pragma once

namespace Synapse
{


namespace MemoryManager
{



template<class T> class Ref
{

};





inline bool g_wasShutDownMethodCalled = false;



static void Initializer()
{

}

template<typename T, typename... Args> static void Alloc(T *ptr, Args... args)
{
    ptr = (ptr!=nullptr) ? new T(args...) : new T();
}

template<typename T> static void Clean(T *ptr)
{
    if(ptr!=nullptr)
    {
        delete ptr;
    }
}

template<typename T>
unsigned int GetPointerArraySize(T *arr)
{
    unsigned int i=0;
    while((arr+i) != nullptr)
        ++i;
    return i;
}

}   //namespace MemoryManager


}



