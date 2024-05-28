//#include "../entity/entitiesAttributesData.hpp"
#include "InitializeEngine.hpp"
#include "../entity/entitiesAttributesData.hpp"
#include "../debug/RenderingInfoLog.hpp"
#include "../multithreading/runParallel.hpp"

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

#endif

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


void Engine::LoadEntities()
{

    //will decrease the loading time of the Engine with 10s and thousands of object initialization

    namespace data = entitiesData;

    std::clog << "Constructing the entities!" << '\n';
    std::clog << "Loading..." << '\n';

    constexpr std::size_t totalEntities = 30003;
    m_entities.reserve(totalEntities);

    //even though there are no shader files for the ground and anotherCube as given below in the entity constructor but still it is running.
    //will fix it.
    m_entities.push_back(new Entity(data::cubeVerticiesData, data::cubeTotalVerticies,
                                  data::cubeIndiciesData, data::cubeTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    m_entities.push_back(new Entity(data::groundVerticiesData, data::groundTotalVerticies,
                                  data::groundIndiciesData, data::groundTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    m_entities.push_back(new Entity(data::anotherCubeVerticiesData, data::anotherCubeTotalVerticies,
                                  data::anotherCubeIndiciesData, data::anotherCubeTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    //initialize the other null entities
    //for now this is because of the benchmarking
    for (std::size_t i = 3; i < totalEntities; ++i)
    {
        m_entities.push_back(new Entity(nullptr, 0, nullptr, 0, "", ""));
    }

    //load the shaders of the entities
    for (auto entity: m_entities)
    {
        entity->LoadShader();
    }

}


void Engine::LoadCamera()
{
    m_camera = new Camera();
    Camera::SetupMouse(m_window->WindowAddress());

    //giving one single shader program id of one entity also renders all the other entities
    //will see this
    //camera->setShaderProgramID(entities[0]->getShader().ProgramID());
#ifdef __LOADTIME__MULTITHREADING__
    omp_set_num_threads(4);
#pragma omp parallel for
#endif
    for (std::size_t i=0; i<m_entities.size(); ++i)
    {
        m_camera->AddShaderProgramID(m_entities[i]->GetShader().ProgramID());
    }
}


void Engine::LoadRenderer()
{
    //renderer = Renderer(entities.size());
    m_renderer = new EntityRenderer(m_entities.size());

#ifdef __LOADTIME__MULTITHREADING__
    omp_set_num_threads(4);
#pragma omp parallel for
#endif
    for (std::size_t i=0; i<m_entities.size(); ++i)
    {
        m_renderer->InitVAO(m_entities[i]->GetVertexObjects().GetVAO());
        m_renderer->InitIndicies(m_entities[i]->TotalIndicies());
    }

    //will add other types of renderers for other Game Engine Objects
}


int8_t Engine::Init()
{
    this->LoadGLFW();
    this->LoadWindow();
    this->LoadGLAD();
    this->SetViewPort();
    this->LoadEntities();
    this->LoadCamera();
    this->LoadRenderer();

    return __SUCCESS__;
}


int8_t Engine::Run()
{
    //core Engine loop
    while (m_window->Running())
    {
        m_renderer->_zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);

        m_window->GetKeyboardInput();
        m_camera->GetKeyboardInput(m_window->WindowAddress());

        m_camera->Update();


#ifdef __RUNTIME__MULTITHREADING__
        Synapse::Threading::S_pragma_omp_parallel_loop<void, std::size_t>(0, m_entities.size(), 4,
        [this](auto i) -> void
        {
            m_entities[i]->Update();
        });

#elif defined(__SINGLETHREADING__)
        for(auto entity : m_entities)
        {
            entity->Update();
        }
#endif


        //make any modification to the entities or entity after running useProgram() and before rendering otherwise it would be TOO bad!

//        entities[0]->getTransformation().translate(glm::vec3(0.0f, -0.01f, 0.0f));
//        entities[0]->getTransformation().modelLocation(entities[0]->getShader().ProgramID());


#if 1

//        for(const auto entity : entities)
//        {
//            entity->translate(glm::vec3(-0.01f, -0.01f, -0.01f));
//        }

//        std::for_each(std::execution::par, entities.begin(), entities.end(), [&](auto entity)->void
//        {
//            entity->getTransformation().translate(vecs[i]);
//            entity->getTransformation().modelLocation(entity->getShader().ProgramID());
//            ++i;
//        });
//
//        i=0;
        //compute_in_parallel();

#else
        m_entities[0]->translate(glm::vec3(0.0f, -0.01f, 0.0f));
#endif

//        GLuint transformationLocation = glGetUniformLocation(entities[0]->getShader().ProgramID(), "transform");
//        glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, glm::value_ptr(transformation));
//
//        transformation = glm::translate(transformation, glm::vec3(0.0f, 1.0f, 0.0f));



#ifdef __UTILIZE__BRANCHPREDICTION__
        //using this is faster cause CPU can predict what the next memory location is going to be (using the L1 cache memory && branch prediction)
        //see the definition of this function. It's also multithreaded

        //renderer.renderEntities();
        m_renderer->Render();
#else
        //doing this is slower cause everytime the CPU needs to access the location in slow memroy
        for(auto entity : entities)
        {
            entity->Render();
        }
#endif


        //this is definately not for benchmarking
        renderingInfo::FramesPerSecond();

        m_window->SwapBuffers();
        m_window->PollEvents();
    }

    return __SUCCESS__;
}


}

































