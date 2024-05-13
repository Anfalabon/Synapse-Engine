//#include "../entity/entitiesAttributesData.hpp"
#include "InitializeEngine.hpp"
#include "../entity/entitiesAttributesData.hpp"
#include "../debug/RenderingInfoLog.hpp"

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
void _zBufferBg(float r, float g, float b, float w)
{
    glClearColor(r, g, b, w);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef STRUCTURED

void Engine::setEntities()
{
    entities.reserve(3);


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

}





int8_t Engine::Init()
{
    //initialize the glfw functions and other glfw features
    if (!glfwInit())
    {
        std::cerr << "Falied to initialize glfw!" << '\n';
        return -1;
    }

    Window window = Window(1920.0f, 1080.0f, "Simulation Engine");

    camera = new Camera();
    Camera::setupMouse(window.windowAddress());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to load GLAD" << '\n';
        return -1;
    }

    //Camera::setupMouse(window.windowAddress());

    glViewport(0, 0, window.WIDTH(), window.HEIGHT());

    this->setEntities();

    for(auto entity : entities)
    {
        camera->setShaderProgramID(entity->getShader().ProgramID());
    }

    return SUCCESS;

}




int8_t Engine::Run()
{
    while(window.running())
    {
        _zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);


#ifdef __MULTITHREADING__
//        std::thread windowKeyInputThread([&window]()->void
//        {
//            window.getKeyboardInput();
//        });
//        std::thread cameraKeyInputThread([&camera, &window]()->void
//        {
//            camera->getKeyboardInput(window.windowAddress());
//        });
//
//        windowKeyInputThread.join();
//        cameraKeyInputThread.join();

        window.getKeyboardInput();
        camera->getKeyboardInput(window.windowAddress());

#else
        window.getKeyboardInput();
        camera->getKeyboardInput(window.windowAddress());
#endif

        camera->update();

#ifdef __DEBUG__
        cube->update();
        ground->update();
        anotherCube->update();

        cube->render();
        ground->render();
        anotherCube->render();
#else

        for(auto entity : entities)
        {
            entity->update();
        }

        //make any modification to the entities or entity after running useProgram() and before rendering otherwise it would be TOO bad!

        entities[0]->getTransformation().translate(glm::vec3(0.0f, -0.01f, 0.0f));
        entities[0]->getTransformation().modelLocation(entities[0]->getShader().ProgramID());

        for(auto entity : entities)
        {
            entity->render();
        }

#endif  //__DEBUG__

        renderingInfo::framesPerSecond();

        window.swapBuffers();
        window.pollEvents();
    }

    return SUCCESS;
}

#else
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




int8_t Engine::Run()
{
    //initialize the glfw functions and other glfw features
    if (!glfwInit())
    {
        std::cerr << "Falied to initialize glfw!" << '\n';
        return -1;
    }

    GLfloat WIDTH = 1920.0f;
    GLfloat HEIGHT = 1080.0f;

    Window window(WIDTH, HEIGHT,"Simulation Engine");

    //simulate a camera
    //Camera *camera = nullptr; //first time got the nullptr derefrencing bug (it gave segmentation fault (core dump))

    Camera *camera = new Camera();
    Camera::setupMouse(window.windowAddress());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to load GLAD" << '\n';
        return -1;
    }

    glViewport(0, 0, window.WIDTH(), window.HEIGHT());






#define __DEVELOPMENT__
//#define __DEBUG__

#define __MULTITHREADING__
//#define __SINGLETHREADING__

#ifdef __DEBUG__

    Entity *cube = new Entity(cubeVerticiesData, cubeTotalVerticies,
                              cubeIndiciesData, cubeTotalIndicies,
                              "../src/shader/GLSL/vertexShaderSource1.glslv",
                              "../src/shader/GLSL/fragmentShaderSource1.glslf");

    Entity *ground = new Entity(groundVerticiesData, groundTotalVerticies,
                                groundIndiciesData, groundTotalIndicies,
                                "../src/shader/GLSL/vertexShaderSource2.glslv",
                                "../src/shader/GLSL/fragmentShaderSource2.glslf");

    Entity *anotherCube = new Entity(anotherCubeVerticiesData, anotherCubeTotalVerticies,
                                     anotherCubeIndiciesData, anotherCubeTotalIndicies,
                                     "../src/shader/GLSL/vertexShaderSource3.glslv",
                                     "../src/shader/GLSL/fragmentShaderSource3.glslf");

#else

    std::vector<Entity*> entities;
    entities.reserve(3);


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

#endif //__DEBUG__



#define INSPECTION_MODE 0
#define GAME_MODE 1


#ifdef __DEBUG__
    //initial position of the camera
    cube->getTransformation().translate(glm::vec3(-0.5f, 10.0f, 0.0f));
    ground->getTransformation().translate(glm::vec3(0.0f, 0.0f, 0.0f));
    anotherCube->getTransformation().translate(glm::vec3(0.0f, 0.0f, 0.0f));

    //set the shader program ID for camera
    camera->setShaderProgramID(cube->getShader().ProgramID());
    camera->setShaderProgramID(ground->getShader().ProgramID());
    camera->setShaderProgramID(anotherCube->getShader().ProgramID());
#else


    for(auto entity : entities)
    {
        camera->setShaderProgramID(entity->getShader().ProgramID());
    }

    //camera->setShaderProgramID(entities[1]->getShader().ProgramID());

//    entities[0]->getTransformation().translate(glm::vec3(0.0, 0.0f, 0.0f));
//    entities[1]->getTransformation().translate(glm::vec3(0.0f, 0.0f, 0.0f));
//    entities[2]->getTransformation().translate(glm::vec3(0.0f, 0.0f, 0.0f));

    //entities[0]->m_transform.translate(glm::vec3(1.0f, 0.0f, 0.0f));

//    entities[0]->getShader().useProgram();
//    entities[0]->m_transform.m_model = glm::rotate(entities[0]->m_transform.m_model, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));


#endif

    std::vector<std::thread> entitiesThreads;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//from here the run function should start and everything before should be inside the Engine constructor or a function named Init()
//which will initialize the window, glad, camera, scenes, entities, Engine mode etc.

    //using namespace renderingInfo;
    //main Engine loop
    while(window.running())
    {
        _zBufferBg(0.2f, 0.3f, 0.3f, 1.0f);


#ifdef __MULTITHREADING__
        std::thread windowKeyInputThread([&window]()->void
        {
            window.getKeyboardInput();
        });
        std::thread cameraKeyInputThread([&camera, &window]()->void
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

#ifdef __DEBUG__
        cube->update();
        ground->update();
        anotherCube->update();

        cube->render();
        ground->render();
        anotherCube->render();
#else

        for(auto entity : entities)
        {
            entity->update();
        }

        //make any modification to the entities or entity after running useProgram() and before rendering otherwise it would be TOO bad!

        entities[0]->getTransformation().translate(glm::vec3(0.0f, -0.01f, 0.0f));
        entities[0]->getTransformation().modelLocation(entities[0]->getShader().ProgramID());

        for(auto entity : entities)
        {
            entity->render();
        }

#endif  //__DEBUG__

        renderingInfo::framesPerSecond();

        window.swapBuffers();
        window.pollEvents();
    }


    delete camera;

    return 0;
}

#endif //STRUCTURED





































