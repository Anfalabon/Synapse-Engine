#include "../scene/entitiesAttributesData.hpp"
#include "Application.hpp"
#include "../scene/entitiesAttributesData.hpp"
#include "../debug/RenderingInfoLog.hpp"
#include "../multithreading/runParallel.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <vector>



#define __SUCCESS__ 1;

#define __RELEASE__
//#define __DEBUG__

//#ifdef __RELEASE__
//#include "../multithreading/defineMultithreadingMacros.hpp"
//#endif

#if defined(__RELEASE__)
    #define __UTILIZE__BRANCHPREDICTION__
    #define __RUNTIME__MULTITHREADING__
    //#define __LOADTIME__MULTITHREADING__
#elif defined(__DEBUG__)
    #define __SINGLETHREADING__
#endif




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
    m_window->Init();
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


void Engine::LoadEntitiesStatically()
{

    //will decrease the loading time of the Engine with 10s and thousands of object initialization

    namespace data = entitiesData;


    std::clog << "Constructing the entities!" << '\n';
    std::clog << "Loading..." << '\n';

    constexpr std::size_t nullEntities = 0;
    //m_entities.reserve(totalEntities);

    //even though there are no shader files for the ground and anotherCube as given below in the scene constructor but still it is running.
    //will fix it.

#define __LOAD_ENTITIES_STATICALLY__
#ifdef __LOAD_ENTITIES_STATICALLY__

    //iam suspecting shaders for this issue


    m_entities.push_back(new RenderableObject("cube",
                                    data::cubeData::cubeVerticiesData, data::cubeData::cubeTotalVerticies,
                                    data::cubeData::cubeIndiciesData, data::cubeData::cubeTotalIndicies,
                                    "../src/shader/GLSL/vertexShaderSource1.glslv",
                                    "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    m_entities.push_back(new RenderableObject("ground",
                                              data::groundData::groundVerticiesData, data::groundData::groundTotalVerticies,
                                              data::groundData::groundIndiciesData, data::groundData::groundTotalIndicies,
                                              "../src/shader/GLSL/vertexShaderSource1.glslv",
                                              "../src/shader/GLSL/fragmentShaderSource1.glslf"));

//    //m_entities[0]->GetShader().RemoveShaders();
//
//    //m_entities.pop_back();
//
    m_entities.push_back(new RenderableObject("anotherCube",
                                              data::anotherCubeData::anotherCubeVerticiesData, data::anotherCubeData::anotherCubeTotalVerticies,
                                              data::anotherCubeData::anotherCubeIndiciesData, data::anotherCubeData::anotherCubeTotalIndicies,
                                              "../src/shader/GLSL/vertexShaderSource1.glslv",
                                              "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    //m_entities[1]->GetShader().RemoveShaders();

//    unsigned int entityIndex = 0;
//
//    m_entities[entityIndex]->Update();
//
////    GLuint transformationLocation = glGetUniformLocation(m_entities[entityIndex]->GetShader().ProgramID(), "model");
////    glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, glm::value_ptr(m_entities[entityIndex]->m_model));
//
//    m_entities[0]->m_model = glm::translate(m_entities[entityIndex]->m_model, glm::vec3(0.0f, -1.0f, 0.0f));



#endif


//    if(m_entities.size() <= 0)
//    {
//        return;
//    }

    if(nullEntities > m_entities.size())
    {
        //for now this is because of the benchmarking
        //add null entities
        for(std::size_t i=m_entities.size(); i<nullEntities; ++i)
        {
            m_entities.push_back(new RenderableObject("", nullptr, 0, nullptr, 0, "", ""));
        }
    }

    if(m_entities.size() > 0)
    {
        //load the shaders of the entities
        for (RenderableObject *entity: m_entities)
        {
            entity->LoadShader();
        }
    }
}





void Engine::LoadScene()
{
    m_scene = new Scene();
    m_scene->Init();
}


void Engine::LoadCamera()
{
    m_camera = new Camera();
    Camera::SetupMouse(m_window->WindowAddress());

#ifdef __LOADTIME__MULTITHREADING__
    omp_set_num_threads(4);
#pragma omp parallel for
#endif

    for(std::size_t i=0; i<m_scene->GetTotalSceneObjects(); ++i)
    {
        m_camera->AddShaderProgramID(m_scene->GetRenderableObject(i)->GetShader().ProgramID());
    }
    //giving one single shader program id of one scene also renders all the other entities
    //will fix this
    //m_camera->AddShaderProgramID(m_scene->GetRenderableObject(0)->GetShader().ProgramID());
    //m_camera->AddShaderProgramID(m_entities[0]->GetShader().ProgramID());
}



//this is kind of useless if 'm_renderer->Render(m_scene)' is used
void Engine::LoadRenderer()
{
    //EntityRenderer *entityRenderer = new EntityRenderer(m_entities.size());
    //m_renderer = new EntityRenderer();

    //this is not that necessary if performence is a big consideration
    //preallocates heap memory
    m_renderer = new EntityRenderer(m_scene->GetTotalSceneObjects());

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

    //will add other types of renderers for other Game Engine Objects(if needed)
}




int8_t Engine::Init()
{
    //these function call orders definately matters
    this->LoadGLFW();
    this->LoadWindow();
    this->LoadGLAD();
    this->SetViewPort();
    this->LoadScene();
    //this->LoadEntitiesStatically();
    this->LoadCamera();
    //this->LoadRenderer();

    return __SUCCESS__;
}




//void Engine::Update()
//{
//    m_renderer->_zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);
//
//    m_window->GetKeyboardInput();
//    m_camera->GetKeyboardInput(m_window->WindowAddress());
//
//    m_scene->Update(m_window->WindowAddress());
//    m_renderer->Render(m_scene);
//    m_camera->Update();
//
//    m_window->SwapBuffers();
//    m_window->PollEvents();
//}


void Engine::Run()
{
    //core Engine loop
    while(m_window->Running())
    {
        m_renderer->_zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);

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



Engine::~Engine()
{
    //thought of letting the os do this.
    //but more writing is kind of fun :)
    Clean(m_camera);
    Clean(m_window);
    Clean(m_scene);
    Clean(m_renderer);
}




}

































