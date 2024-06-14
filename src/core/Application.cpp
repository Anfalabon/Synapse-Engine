#include "Application.hpp"
#include <GLFW/glfw3.h>


namespace Synapse
{

//for now the 'Init', 'Run' and  'ShutDown' Method in Application class fully and singlely depends on Engine.

bool Application::Init()
{
    m_engine = new Engine();
    return m_engine->Init();
}

//for now window is being used in 'Engine'. So no need for this
bool Application::IsWindowRunning()
{
    return m_engine->GetWindow()->IsRunning();
}

void Application::Run()
{
    m_engine->Run();
}

bool Application::IsRestart()
{
    return m_engine->m_engineRestart;
}

void Application::ShutDown()
{
    m_engine->ShutDown();
    delete m_engine;
}


}

























