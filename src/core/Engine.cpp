#include "Engine.hpp"
#include "../debug/LOG.hpp"
#include "../debug/RenderingInfoLog.hpp"
#include "../utils/MemoryManager.hpp"

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <iostream>



#if  defined(__RUNTIME__MULTITHREADING__) || defined(__LOADTIME__MULTITHREADING__)

#include <thread>
#include <omp.h>
#include <algorithm>    //std::execution::policy in std::for_each()
#include <execution>

#endif



//the braces style is inconsistent(not next line) here because i like to use 'extern "C"' perticularly in this way
extern "C"{
    inline void FramesPerSecond();

    //in windows the following is used for importing or exporting shared library functions with C linkage(MSVC obviously)
    //__declspec(dllimport)
    //__declspec(dllexport)

    //in linux the way is different and often certian attribute is used for the same purpose
    //__attribute__((visibility("default")))
}

namespace Synapse
{



int8_t Engine::LoadGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "Falied to initialize glfw!" << '\n';
        return -1;
    }
    return 0;
}


void Engine::LoadWindow()
{

    m_window = new Window(1920.0f, 1080.0f, "Simulation Engine");
    bool isWindowInitSuccess = m_window->Init();
    std::cout << "Initialized the window!" << '\n';
}


int8_t Engine::LoadGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cerr << "Failed to load GLAD" << '\n';
        return -1;
    }
    return 0;
}


void Engine::SetViewPort()
{
    glViewport(0, 0, m_window->WIDTH(), m_window->HEIGHT());
}


void Engine::LoadScene()
{
    std::cout << "Initialized initial scene" << '\n';
    m_scene = new Scene();
    m_scene->Init();
}



void Engine::LoadCamera()
{
    std::cout << "Going to initialize the Camera" << '\n';
#ifdef Alloc
    MemoryManager::Alloc(m_camera);
#else
    //will do nullptr checking
    //m_camera = new Camera();

    std::size_t totalCameras = 2;
    for(std::size_t i=0; i<totalCameras; ++i)
    {
        m_cameras.push_back(new Camera());
    }


    std::cout << "pushed cameras to the std::vector!" << '\n';

#endif

   //we need multiple of these
   //right now we can't as it is a static function
    Camera::SetupMouse(m_window->WindowAddress());

#ifdef __LOADTIME__MULTITHREADING__
    omp_set_num_threads(4);
    #pragma omp parallel for
#endif

//    for(std::size_t i=0; i<m_scene->GetTotalSceneObjects(); ++i)
//    {
//        m_camera->AddShaderProgramID(m_scene->GetRenderableObject(i)->GetShader().ProgramID());
//    }

    for(std::size_t j=0; j<totalCameras; ++j)
    {
        for(std::size_t i=0; i<m_scene->GetTotalSceneObjects(); ++i)
        {
            m_cameras[j]->AddShaderProgramID(m_scene->GetRenderableObject(i)->GetShader().ProgramID());
        }
    }




    std::cout << "Initialized the Camera" << '\n';
    //giving one single shader program id of single scene object also renders all the other objects
    //will fix this
    //m_camera->AddShaderProgramID(m_scene->GetRenderableObject(0)->GetShader().ProgramID());
    //m_camera->AddShaderProgramID(m_entities[0]->GetShader().ProgramID());

}



//this is kind of useless if 'm_renderer->Render(m_scene)' is used
void Engine::LoadRenderer()
{
    //will do nullptr checking

    //this is not that much necessary unless performence is a big consideration
    //preallocates heap memory
    m_renderer = new SceneRenderer(m_scene->GetTotalSceneObjects());

#ifdef __LOADTIME__MULTITHREADING__
    omp_set_num_threads(4);
#pragma omp parallel for
#endif

    for(std::size_t i=0; i<m_scene->GetTotalSceneObjects(); ++i)
    {
        //here once used '0' instead of 'i' in GetRenderableObject() function arg
        //so it was only rendering the first object inside scene's renderable objects buffer.
        //wasted hours for this lol.
        m_renderer->InitVAO(m_scene->GetRenderableObject(i)->GetVertexObjects().GetVAO());
        m_renderer->InitIndicies(m_scene->GetRenderableObject(i)->TotalIndicies());
    }

    std::cout << "Initialized Renderer" << '\n';

    //will add other types of renderers for other Game Engine Objects(if needed)
}




int8_t Engine::Init()
{
#define __SUCCESS__ 1;
    //these function call orders definately matters
    this->LoadGLFW();
    this->LoadWindow(); //not loading the 'Window' causes uninitialization of GLAD too!
    this->LoadGLAD();
    this->SetViewPort();
    this->LoadScene();
    this->LoadCamera();
    //this->LoadRenderer();

    std::cout << "Initialized the Engine" << '\n';

    return __SUCCESS__;
}



void Engine::SelectCamera()
{
    if(glfwGetKey(m_window->WindowAddress(), GLFW_KEY_F1) == GLFW_PRESS)
    {
        m_currentCameraIndex = 0;
    }
    else if(glfwGetKey(m_window->WindowAddress(), GLFW_KEY_F2) == GLFW_PRESS)
    {
        m_currentCameraIndex = 1;
    }

    std::cout << "Current Camera running: " << m_currentCameraIndex << '\n';
}


void Engine::Update()
{
    m_renderer->_zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);

    m_window->GetKeyboardInput();
    this->SelectCamera();
    //m_camera->GetKeyboardInput(m_window->WindowAddress());
    m_cameras[m_currentCameraIndex]->GetKeyboardInput(m_window->WindowAddress());


    m_scene->Update(m_window->WindowAddress());
    m_renderer->Render(m_scene);
    //m_camera->Update();
    m_cameras[m_currentCameraIndex]->Update();

    //this is definately not for benchmarking
    renderingInfo::FramesPerSecond();

    m_window->SwapBuffers();
    m_window->PollEvents();
}


void Engine::Run()
{
    std::cout << "Going to run the Engine" << '\n';
    //core Engine loop
    while(m_window->IsRunning())
    {
        m_renderer->_zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);

        //will use 'event' system for these two bad boys
        m_window->GetKeyboardInput();
        m_camera->GetKeyboardInput(m_window->WindowAddress());

        m_scene->Update(m_window->WindowAddress());
        m_renderer->Render(m_scene);
        m_camera->Update();

        //this is definately not for benchmarking
        renderingInfo::FramesPerSecond();

        m_window->SwapBuffers();
        m_window->PollEvents();
    }

}



void Engine::ShutDown()
{
    //thought of letting the os do this.
    //but more writing is kind of fun :)
    MemoryManager::Clean<Camera>(m_camera);
    MemoryManager::Clean<Window>(m_window);
    MemoryManager::Clean<Scene>(m_scene);
    MemoryManager::Clean<Renderer>(m_renderer);

    MemoryManager::g_wasShutDownMethodCalled = true;
}


Engine::~Engine()
{
    //thought of letting the os do this.
    //but more writing is kind of fun :)
    if(!MemoryManager::g_wasShutDownMethodCalled)
    {
        this->ShutDown();
    }
}







}   //namespace Synapse
