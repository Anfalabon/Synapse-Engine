//#include "../entity/entitiesAttributesData.hpp"
#include "InitializeEngine.hpp"
#include "../entity/entitiesAttributesData.hpp"
#include "../debug/RenderingInfoLog.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <thread>
#include <omp.h>


namespace data = entitiesData;

#define SUCCESS 1

#define __DEVELOPMENT__
//#define __DEBUG__

#define __MULTITHREADING__
//#define __SINGLETHREADING__




int8_t Engine::loadGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "Falied to initialize glfw!" << '\n';
        return -1;
    }
    return 0;
}

void Engine::loadWindow()
{
    window = new Window(1920.0f, 1080.0f, "Simulation Engine");
    window->init();
}


int8_t Engine::loadGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to load GLAD" << '\n';
        return -1;
    }
    return 0;
}


void Engine::setViewPort()
{
    glViewport(0, 0, window->WIDTH(), window->HEIGHT());
}


std::mutex m;



void Engine::loadEntities()
{
    std::clog << "Constructing the entities!" << '\n';
    std::clog << "Loading..." << '\n';

    constexpr std::size_t totalEntities = 30000;
    entities.reserve(totalEntities);

    entities.push_back(new Entity(data::cubeVerticiesData, data::cubeTotalVerticies,
                                  data::cubeIndiciesData, data::cubeTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    entities.push_back(new Entity(data::groundVerticiesData, data::groundTotalVerticies,
                                  data::groundIndiciesData, data::groundTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    entities.push_back(new Entity(data::anotherCubeVerticiesData, data::anotherCubeTotalVerticies,
                                  data::anotherCubeIndiciesData, data::anotherCubeTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));


#if 1

    for(std::size_t i=0; i<totalEntities; ++i)
    {
        entities.push_back(new Entity(nullptr, 0, nullptr, 0, "", ""));
    }

    for(auto entity : entities)
    {
        entity->loadShader();
    }

    for(auto entity : entities)
    {
        renderer.initVAO(entity->getVertexObjects().getVAO());
        renderer.initIndicies(entity->totalIndicies());
    }


#else

#if 1
    //#pragma omp parallel for
    for(std::size_t i=0; i<totalEntities; ++i)
    {
        entities.push_back(new Entity(nullptr, 0, nullptr, 0, "", ""));

        entities[i]->loadShader();

        renderer.initVAO(entities[i]->getVertexObjects().getVAO());
        renderer.initIndicies(entities[i]->totalIndicies());

        //camera->addShaderProgramID(entities[i]->getShader().ProgramID());
    }
#else
    for(auto entity : entities)
    {
        entities.push_back(new Entity(nullptr, 0, nullptr, 0, "", ""));

        entity->loadShader();

        renderer.initVAO(entity->getVertexObjects().getVAO());
        renderer.initIndicies(entity->totalIndicies());

        //camera->addShaderProgramID(entity->getShader().ProgramID());
    }
#endif


#endif
}


void Engine::loadCamera()
{
    camera = new Camera();
    Camera::setupMouse(window->windowAddress());

    //giving one single shader program id of one entity also renders all the other entities
    //will see this
    //camera->setShaderProgramID(entities[0]->getShader().ProgramID());
    for(std::size_t i=0; i<entities.size(); ++i)
    {
        camera->addShaderProgramID(entities[i]->getShader().ProgramID());
    }
}


void Engine::loadRenderer()
{
    //this is only for entities renderer.
    renderer = Renderer(entities.size());
//    for(std::size_t i=0; i<entities.size(); ++i)
//    {
//        renderer.initVAO(entities[i]->getVertexObjects().getVAO());
//        renderer.initIndicies(entities[i]->totalIndicies());
//    }

    //will add other types of renderers for other Game Engine Objects
}



int8_t Engine::Init()
{
    this->loadGLFW();
    this->loadWindow();
    this->loadGLAD();
    this->setViewPort();
    this->loadEntities();
    this->loadCamera();
    this->loadRenderer();

    return isInitSuccess;
}



int8_t Engine::Run()
{

//will use multithreading for updating and redering the entities

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//from here the run function should start and everything before should be inside the Engine constructor or a function named Init()
//which will initialize the window, glad, camera, scenes, entities, Engine mode etc.

    //using namespace renderingInfo;
    //main Engine loop
    while(window->running())
    {
        renderer._zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);

        window->getKeyboardInput();
        camera->getKeyboardInput(window->windowAddress());


        camera->update();

#ifdef __MULTITHREADING__
        omp_set_num_threads(4);
        #pragma omp parallel for
#endif
        for(auto entity : entities)
        {
            entity->update();
        }

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

#else
        entities[0]->translate(glm::vec3(0.0f, -0.01f, 0.0f));
#endif

//        GLuint transformationLocation = glGetUniformLocation(entities[0]->getShader().ProgramID(), "transform");
//        glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, glm::value_ptr(transformation));
//
//        transformation = glm::translate(transformation, glm::vec3(0.0f, 1.0f, 0.0f));

#if 0
        for(auto entity : entities)
        {
            entity->render();
        }
#else
        renderer.renderEntities();
#endif
        //this is definately not for benchmarking
        renderingInfo::framesPerSecond();

        window->swapBuffers();
        window->pollEvents();
    }

    return 0;
}






































