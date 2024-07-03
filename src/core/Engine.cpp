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

    //m_scene->GetRenderableObject(2)->GetShader().UseProgram();
//    m_scene->GetRenderableObject(1)->GetShader().UseProgram();
//    m_scene->GetRenderableObject(2)->GetShader().UseProgram();

    //m_scene->GetRenderableObject(0)->GetShader().SendMatrix4ToGPU("model", m_scene->GetRenderableObject(0)->m_model);
//    m_scene->GetRenderableObject(1)->GetShader().SendMatrix4ToGPU("model", m_scene->GetRenderableObject(1)->m_model);
//    m_scene->GetRenderableObject(2)->GetShader().SendMatrix4ToGPU("model", m_scene->GetRenderableObject(2)->m_model);

    //m_scene->GetRenderableObject(2)->GetShader().UseProgram();


}



void Engine::LoadCameras()
{
    std::cout << "Going to initialize the Camera" << '\n';
#ifdef Alloc
    MemoryManager::Alloc(m_camera);
#else
    //will do nullptr checking
    //m_camera = new Camera();

    std::size_t totalCameras = 3;
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


//    for(std::size_t j=0; j<totalCameras; ++j)
//    {
//        for(std::size_t i=0; i<m_scene->GetTotalSceneObjects(); ++i)
//        {
//            m_cameras[j]->AddShaderProgramID(m_scene->GetRenderableObject(i)->GetShader().ProgramID());
//        }
//    }

    // std::cout << "Initialized the Camera" << '\n'; 

    std::size_t j = 0;
    std::size_t i = 0;
    for(; i<m_scene->GetTotalSceneObjects() && j<m_cameras.size(); ++i, ++j)
    {
        //m_cameras[j]->AddShaderProgramID(m_scene->GetRenderableObject(i)->GetShader().ProgramID());
        m_cameras[j]->AddShaderProgramID(m_renderer->GetShader(0).GetProgramID());
    }

//    for(std::size_t i=0; i<m_scene->GetTotalSceneObjects(); ++i)
//    {
//        m_cameras[i]->AddShaderProgramID(m_renderer->GetShader(0).GetProgramID());
//    }



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
    m_renderer = new SceneRenderer();

#ifdef __LOADTIME__MULTITHREADING__
    omp_set_num_threads(4);
#pragma omp parallel for
#endif



    std::cout << "Initialized Renderer" << '\n';



    //these shader files locations are relative to the 'Makefile' in 'build' directory
    m_renderer->AddShader("../src/renderer/shader/GLSL/vertexShader1.vert",
                           "../src/renderer/shader/GLSL/fragmentShader1.frag");
    m_renderer->SetShader();
    m_renderer->GetShader(0).UseProgram();


//    m_renderer->AddShader("../src/renderer/shader/GLSL/vertexShader1.vert",
//                          "../src/renderer/shader/GLSL/groundFragmentShader.frag");
//    m_renderer->SetShader();
//    m_renderer->GetShader(1).UseProgram();



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
    this->LoadRenderer();
    this->LoadCameras();

    std::cout << "Initialized the Engine" << '\n';

    return __SUCCESS__;
}



void Engine::SelectCamera()
{
#if 0
    bool exit = false;
    auto getCamera = [&exit, this](unsigned short cameraNum)->void
    {
        std::cout << "Running Camera selector!" << '\n';
        if(exit)
        {
            return;
        }
        else if(glfwGetKey(m_window->WindowAddress(), GLFW_KEY_F1 + cameraNum) == GLFW_PRESS)    //290
        {
            m_currentCameraIndex = cameraNum;
            exit = true;
        }
    };
    for(unsigned short i=0; i<m_cameras.size() && !exit; ++i) [[likely]]
    {
        getCamera(i);
    }
#endif

    if(glfwGetKey(m_window->WindowAddress(), GLFW_KEY_F1) == GLFW_PRESS)    //290
    {
        m_currentCameraIndex = 0;
    }
    else if(glfwGetKey(m_window->WindowAddress(), GLFW_KEY_F2) == GLFW_PRESS)
    {
        m_currentCameraIndex = 1;
    }
    else if(glfwGetKey(m_window->WindowAddress(), GLFW_KEY_F3) == GLFW_PRESS)
    {
        m_currentCameraIndex = 2;
    }


    //DEBUG::__LOG__MANAGER__::LOG("Current Camera running: ");
    std::cout << "Current Camera running: " << m_currentCameraIndex << '\n';
}


bool Engine::Restart()
{
    return (glfwGetKey(m_window->WindowAddress(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS &&
            glfwGetKey(m_window->WindowAddress(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS &&
            glfwGetKey(m_window->WindowAddress(), GLFW_KEY_R) == GLFW_PRESS) ? true : false;
}


#ifdef __UPDATE__ENGINE__

void Engine::Update()
{
    m_renderer->SetBackGround(0.2f, 0.3f, 0.3f, 1.0f);
    m_renderer->UseZbuffer();

    //m_renderer->_zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);
    //will use 'event' systems for these two bad boys
    m_window->GetKeyboardInput();
    this->SelectCamera();
    m_cameras[m_currentCameraIndex]->GetKeyboardInput(m_window->WindowAddress());

    m_scene->Update(m_window->WindowAddress());
    m_renderer->Render(m_scene);
    m_cameras[m_currentCameraIndex]->Update();

    //this is definately not for benchmarking
    renderingInfo::FramesPerSecond();

    m_window->SwapBuffers();
    m_window->PollEvents();
}

#elif defined(__RUN__ENGINE__)

void Engine::Run()
{
    DEBUG::__LOG__MANAGER__::LOG("Going to run the Engine");

    srand(static_cast <unsigned> (time(0)));

    //m_scene->GetRenderableObject(0)->GetShader().UseProgram();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    //core Engine loop
    while(m_window->IsRunning())
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        std::cout << "Delta time is: " << deltaTime << '\n';

        //this should be inside 'm_window->GetKeyboardInput();'
        if(this->Restart())
        {
            m_engineRestart = true;
            m_window->ShutDown();
            break;
        }

        m_renderer->SetBackGround(0.2f, 0.3f, 0.3f, 1.0f);
        //m_renderer->SetBackGround(0.423f, 0.646f, 0.738f, 1.0f);
        m_renderer->UseZbuffer();

        //will use 'event' systems for these two bad boys
        m_window->GetKeyboardInput();
        this->SelectCamera();
        m_cameras[m_currentCameraIndex]->GetKeyboardInput(m_window->WindowAddress());

        m_scene->Update(m_window->WindowAddress(), m_cameras[m_currentCameraIndex]->GetTargetPos(),
                        m_cameras[m_currentCameraIndex]->GetPos(),
                        m_cameras[m_currentCameraIndex]->GetYaw(),
                        m_cameras[m_currentCameraIndex]->GetPitch(), deltaTime);
        m_renderer->Render(m_scene);
        m_cameras[m_currentCameraIndex]->Update(m_scene->GetRenderableObjects());

        //this is definately not for benchmarking
        renderingInfo::FramesPerSecond();

        m_window->SwapBuffers();
        m_window->PollEvents();
    }

}

#endif


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
