#include "Engine.hpp"
#include "debug/LOG.hpp"
#include "debug/RenderingInfoLog.hpp"
#include "core/MemoryManager.hpp"
#include "camera/Cursor.hpp"


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
    if(isWindowInitSuccess)
    {
        //Window::FrameBufferSizeCallback();
        //std::cout << "Failed to initialize the window!" << '\n';
        return;
    }
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


void Engine::LoadAudioEngine()
{
    m_audio = new Synapse::Audio();
}



void Engine::LoadScene()
{
    std::cout << "Initialized initial scene" << '\n';
    m_scene = new Scene();
    m_scene->Init();
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
        m_cameras.push_back(new Camera(i, Camera::PROJECTION_TYPES::PERSPECTIVE));
    }

    std::cout << "pushed cameras to the std::vector!" << '\n';

#endif

    //we need multiple of these
    //right now we can't as it is a static function
    //Camera::SetupMouse(m_window->WindowAddress());
    for(std::size_t i=0; i<m_cameras.size(); ++i)
    {
        m_cameras[i]->SetupMouse(m_window->WindowAddress());
    }

#ifdef __LOADTIME__MULTITHREADING__
    omp_set_num_threads(4);
    #pragma omp parallel for
#endif


    for(std::size_t j=0; j<m_cameras.size(); ++j)
    {
        for(std::size_t i=0; i<m_renderer->GetTotalShaders(); ++i)
        {
            //m_cameras[j]->AddShaderProgramID(m_renderer->GetShader(i).GetProgramID());
            m_cameras[j]->AddShader(m_renderer->GetShader(i));
        }
    }

    // std::cout << "Initialized the Camera" << '\n'; 


    std::cout << "Total Scene shaders: " << m_renderer->GetTotalShaders() << '\n';
    std::cout << "Total Scene objects: " << m_scene->GetTotalSceneObjects() << '\n';


//    for(std::size_t i=0; i<m_scene->GetTotalSceneObjects(); ++i)
//    {
//        m_cameras[i]->AddShaderProgramID(m_renderer->GetShader(0).GetProgramID());
//    }



    std::cout << "Initialized the Camera" << '\n';


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

    //will add other types of renderers for Game Engine (if needed)
}




int8_t Engine::Init()
{
#define __SUCCESS__ 1;
    //these function call orders definately matters
    this->LoadGLFW();
    this->LoadWindow(); //not loading the 'Window' causes uninitialization of GLAD too!
    this->LoadGLAD();
    this->LoadAudioEngine();
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
    return ((glfwGetKey(m_window->WindowAddress(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS &&
            glfwGetKey(m_window->WindowAddress(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS &&
            glfwGetKey(m_window->WindowAddress(), GLFW_KEY_R) == GLFW_PRESS)) ? true : false;
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



void Engine::CalculateDeltaTime()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
}




void Engine::Run()
{
    DEBUG::__LOG__MANAGER__::LOG("Going to run the Engine");

    srand(static_cast <unsigned> (time(0)));

    //m_scene->GetRenderableObject(0)->GetShader().UseProgram();


    //once it starts to play it won't stop (even for the entire life of the program)
    //will make a function called 'Stop()' or 'Pause()' to stop it.

    //m_audio->Play("../vendor/irrKlang/bell.wav");
    //m_audio->Play("../vendor/irrKlang/Alexander-blu-music-style.wav");

    //core Engine loop
    while(m_window->IsRunning())
    {

        Engine::CalculateDeltaTime();
        std::cout << "Delta time is: " << m_deltaTime << '\n';

        //this should be inside 'm_window->GetKeyboardInput();'
        if(this->Restart())
        {
            m_engineRestart = true;
            m_window->ShutDown();
            //exit(1);
            break;
        }

        m_renderer->SetBackGround(0.2f, 0.3f, 0.3f, 1.0f);
        //will use sin function to move around day and night after a certain period

        m_renderer->UseZbuffer();

        //will use 'event' systems for these two bad boys
        m_window->GetKeyboardInput();

        this->SelectCamera();
        m_cameras[m_currentCameraIndex]->GetKeyboardInput(m_window->WindowAddress(), m_deltaTime);
        //m_scriptingEngine->UpdateScene(m_scene);
        m_scene->Update(m_window->WindowAddress(), m_cameras[m_currentCameraIndex], m_deltaTime);

        m_renderer->Render(m_scene);

        m_cameras[m_currentCameraIndex]->Update(m_scene->GetRenderableObjects(), m_deltaTime);

        //this is definately not for benchmarking
        renderingInfo::FramesPerSecond(m_deltaTime);

        //m_window->SwapBuffers();
        m_frameBuffer->SwapBuffers(m_window->WindowAddress());
        m_window->PollEvents();
    }

}

#endif


void Engine::ShutDown()
{
    m_scene->Clear();

    //thought of letting the os do this.
    //but more writing is kind of fun :)
    MemoryManager::Clean<Synapse::Camera>(m_camera);
    MemoryManager::Clean<Synapse::Window>(m_window);
    MemoryManager::Clean<Synapse::Scene>(m_scene);
    MemoryManager::Clean<Synapse::Renderer>(m_renderer);
    MemoryManager::Clean<Synapse::Audio>(m_audio);

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
