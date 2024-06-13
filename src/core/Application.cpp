#include "Application.hpp"


namespace Synapse
{

//for now the 'Init', 'Run' and  'ShutDown' Method in Application class fully and singlely depends on Engine.

bool Application::Init()
{
    m_engine = new Engine();
    return m_engine->Init();
}

bool Application::IsWindowRunning()
{
    return m_engine->GetWindow()->IsRunning();
}

void Application::Update()
{
    m_engine->Update();
}

void Application::Run()
{
    m_engine->Run();
}

void Application::ShutDown()
{
    m_engine->ShutDown();
    delete m_engine;
}


}

























