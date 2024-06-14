#pragma once

namespace MemoryManager
{

    static bool g_wasShutDownMethodCalled = false;

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

}   //namespace MemoryManager

