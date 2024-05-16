//#include "../entity/entitiesAttributesData.hpp"
#include "InitializeEngine.hpp"
#include "../entity/entitiesAttributesData.hpp"
#include "../debug/RenderingInfoLog.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <thread>
#include <execution>
#include <iterator>
#include <new>


namespace data = entitiesData;

#define SUCCESS 1

#define __DEVELOPMENT__
//#define __DEBUG__

#define __MULTITHREADING__
//#define __SINGLETHREADING__






//set the background color
//enable the depth test (z buffer)
//disable the cull face
//clear the color buffer bit along with depth buffer bit
//also the last parameter isn't 'w' (the homogenious coordinate) it's alpha (the opacity)
void _zBufferBg(float r, float g, float b, float w)
{
    glClearColor(r, g, b, w);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




bool Engine::loadGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "Falied to initialize glfw!" << '\n';
        return 0;
    }
}

bool Engine::loadGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to load GLAD" << '\n';
        return 0;
    }
    glViewport(0, 0, window.WIDTH(), window.HEIGHT());
}

bool Engine::loadCamera()
{
    Camera::setupMouse(window.windowAddress());
    return (camera!=nullptr) ? 1 : 0;
}

bool Engine::loadEntities()
{


    std::clog << "Constructing the entities!" << '\n';
    std::clog << "Loading..." << '\n';

    entities.reserve(initialEntities);

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

    std::size_t i=0;
    while(i!=initialEntities-3)
    {
        entities.push_back(new Entity(nullptr, 0, nullptr, 0, "", ""));
        ++i;
    }

    for(auto entity : entities)
    {
        entity->loadShader();
    }

    for(auto entity : entities)
    {
        camera->setShaderProgramID(entity->getShader().ProgramID());
    }

    return (entities[0]!=nullptr) ? 1 : 0;

}

bool Engine::loadRenderer()
{
    renderer = Renderer(entities.size());
}




int8_t Engine::Init()
{
    if(!isInitSuccess)
    {
        std::cerr << "Failed to initialize glfw!" << '\n';
        return isInitSuccess;
    }

    GLfloat WIDTH = 1920.0f;
    GLfloat HEIGHT = 1080.0f;

    //simulate a camera
    //Camera *camera = nullptr; //first time got the nullptr derefrencing bug (it gave segmentation fault (core dump))
    Camera::setupMouse(window.windowAddress());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to load GLAD" << '\n';
        return -1;
    }

    glViewport(0, 0, window.WIDTH(), window.HEIGHT());

    entities.reserve(initialEntities);
    entities.push_back(new Entity(data::cubeVerticiesData, data::cubeTotalVerticies,
                                  data::cubeIndiciesData, data::cubeTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    entities.push_back(new Entity( data::groundVerticiesData, data::groundTotalVerticies,
                                   data::groundIndiciesData, data::groundTotalIndicies,
                                   "../src/shader/GLSL/vertexShaderSource1.glslv",
                                   "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    entities.push_back(new Entity(data::anotherCubeVerticiesData, data::anotherCubeTotalVerticies,
                                  data::anotherCubeIndiciesData, data::anotherCubeTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

#if 0
    for(std::size_t i=0; i!=initialEntities-3; ++i)
    {
        entities.push_back(new Entity(nullptr, 0, nullptr, 0, "", ""));
    }

    for(auto entity : entities)
    {
        entity->loadShader();
    }

    for(std::size_t i=0; i<initialEntities; ++i)
    {
        renderer.initVAO(entities[i]->getVertexObjects().getVAO());
        renderer.initIndicies(entities[i]->totalIndicies());
    }


    //giving one single shader program id of one entity also renders all the other entities
    //will see this
    //camera->setShaderProgramID(entities[0]->getShader().ProgramID());
    for(auto entity : entities)
    {
        camera->setShaderProgramID(entity->getShader().ProgramID());
    }


    //if we try to load only one entity shader then all the other entities will be rendered
    //but any transformation made to the loaded shader entity will cause change.
    //entities[2]->loadShader();
#else
    //initializing the entities, entities-shader and renderer at the same time
    //will use execution policy : std::execution::par with the g++ or clang++ + stdlibc++ = libc++ Flag
    //with this we will be able to have a less loading time

#ifdef __SINGLETHREADING__
    for(std::size_t i=0; i<initialEntities; ++i)
    {
        entities.push_back(new Entity(nullptr, 0, nullptr, 0, "", ""));

        entities[i]->loadShader();

        renderer.initVAO(entities[i]->getVertexObjects().getVAO());
        renderer.initIndicies(entities[i]->totalIndicies());

        camera->setShaderProgramID(entities[i]->getShader().ProgramID());
    }
#else
    std::for_each(std::execution::par, entities.begin(), entities.end(), [this](auto &entity)->void
    {
        entities.push_back(new Entity(nullptr, 0, nullptr, 0, "", ""));

        entity->loadShader();

        renderer.initVAO(entity->getVertexObjects().getVAO());
        renderer.initIndicies(entity->totalIndicies());

        camera->setShaderProgramID(entity->getShader().ProgramID());
    });
#endif


#endif

    //ignoring this returns causes segmentaion fault(core dump)
    return isInitSuccess;

}

















int8_t Engine::Run()
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//from here the run function should start and everything before should be inside the Engine constructor or a function named Init()
//which will initialize the window, glad, camera, scenes, entities, Engine mode etc.

    //using namespace renderingInfo;
    //main Engine loop
    while(window.running())
    {
        _zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);


#ifdef __MULTITHREADING__
        std::thread windowKeyInputThread([this]()->void
        {
            window.getKeyboardInput();
        });
        std::thread cameraKeyInputThread([this, this]()->void
        {
            camera->getKeyboardInput(window.windowAddress());
        });

        windowKeyInputThread.join();
        cameraKeyInputThread.join();

#else
        window.getKeyboardInput();
        camera->getKeyboardInput(window.windowAddress());
#endif

        camera->update();

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
        renderer.render();
#endif

        //this is definately not for benchmarking
        renderingInfo::framesPerSecond();

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}






































