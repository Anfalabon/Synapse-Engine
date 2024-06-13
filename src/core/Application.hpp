#pragma once

#include "Engine.hpp"


#define PLATFORM

namespace Synapse
{


class [[nodiscard]] PLATFORM Application
{
public:
    Application() = default;
    ~Application() = default;

    static Application &getApplication()
    {
        static Application application;
        return application;
    }

    [[nodiscard]] bool Init();
    void Update();
    void Run();
    [[nodiscard]] bool IsWindowRunning();
    void ShutDown();

private:

    Engine *m_engine;

};



#if defined(__linux__)
    //write application for linux
#elif defined(__WIN32__)
    DEBUG::__LOG__MANAGER__::LOG("WIN32 system not defined yet!");
#elif defined(__MAC__)
    DEBUG::__LOG__MANAGER__::LOG("MAC system not defined yet!");
#elif defined(__FreeBSD__)
    DEBUG::__LOG__MANAGER__::LOG("BSD system not defined yet!");
#elif defined(__ANDROID__)
    DEBUG::__LOG__MANAGER__::LOG("Android system not defined yet!");

#endif

}



