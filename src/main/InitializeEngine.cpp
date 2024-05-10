

#include "InitializeEngine.hpp"
#include "../debug/RenderingInfoLog.hpp"

#include <memory>
#include <vector>
#include <algorithm>
#include <thread>
#include <execution>
#include <iterator>
#include <new>



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



//Engine::Engine()
////    : window(1920.0f, 1080.0f, "Simulation Engine"),
////      camera(new Camera()),
////      cubesAndGround(new Entity())
//{
//    //initialize the glfw functions and other glfw features
//    if (!glfwInit())
//    {
//        std::cerr << "Falied to initialize glfw!" << '\n';
//        return;
//    }
//
//    //simulate a camera
//    //Camera *camera = nullptr; //first time got the nullptr derefrencing bug (it gave segmentation fault (core dump))
//
//    //std::unique_ptr<Camera> camera(new Camera());
//    Camera::setupMouse(window.windowAddress());
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cerr << "Failed to load GLAD" << '\n';
//        return;
//    }
//
//    glViewport(0, 0, window.WIDTH(), window.HEIGHT());
//
//
////    std::vector<Entity*> entities;
////    Entity *cubesAndGround = new Entity();
//
//}


template<typename T>
void clean(T *object)
{
    delete object;
}



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



    //these verticies and indicies data will be in another file and we will get it by using fstream

    GLuint cubeTotalVerticies = 8;
    GLuint cubeTotalIndicies = 36;

    Vertex *cubeVerticiesData = new Vertex[cubeTotalVerticies]{
            //an entity with all unique vertex attributes(shape: cube)
            {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
            {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 1.0f}},
            {{0.5f,  -0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}},
            {{0.5f,  -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
            {{-0.5f, 0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
            {{-0.5f, 0.5f,  -0.5f}, {1.0f, 1.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
    };

    GLuint *cubeIndiciesData = new GLuint[cubeTotalIndicies]{
            //twelf triangles to create a cube(as cube has 6 surfaces and each surface is a rectanle itselft which again is made of 2 triangles)
            0, 1, 2,        //first triangle
            1, 2, 3,        //second triangle
            0, 1, 4,        //third triangle
            1, 4, 5,        //fourth triangle
            4, 5, 6,        //fifth triangle
            5, 6, 7,        //sixth triangle
            2, 3, 6,        //seventh triangle
            3, 6, 7,        //eight triangle
            0, 2, 4,        //ninth triangle
            2, 4, 6,        //tenth triangle
            1, 3, 5,        //eleventh triangle
            3, 7, 5,        //twelfth triangle
    };



    GLuint groundTotalVerticies = 4;
    GLuint groundTotalIndicies = 12;

    Vertex *groundVerticiesData = new Vertex[groundTotalVerticies]{
            {{960.0f,  -0.5f, 540.0f},  {1.0f, 0.0f, 0.0f}},
            {{-960.0f, -0.5f, 540.0f},  {0.0f, 1.0f, 0.0f}},
            {{960.0f,  -0.5f, -540.0f}, {0.0f, 0.0f, 1.0f}},
            {{-960.0f, -0.5f, -540.0f}, {0.5f, 0.5f, 0.5f}},
    };

    GLuint *groundIndiciesData = new GLuint[groundTotalIndicies]{
            0, 1, 2,
            1, 2, 3,
    };



    GLuint anotherCubeTotalVerticies = 8;
    GLuint anotherCubeTotalIndicies = 36;

    Vertex *anotherCubeVerticiesData = new Vertex[anotherCubeTotalVerticies]{
            {{3.0f, 0.5f, 1.0f},    {1.0f, 0.0f, 0.0f}},
            {{3.0f, 0.5f, -1.0f},   {0.0f, 1.0f, 0.0f}},
            {{2.0f, -0.5f, 1.0f},   {0.0f, 0.0f, 1.0f}},
            {{2.0f, -0.5f, -1.0f},  {0.5f, 1.0f, 0.0f}},
            {{3.0f, -0.5f, 1.0f},   {0.0f, 1.0f, 0.0f}},
            {{3.0f, -0.5f, -1.0f},  {0.5f, 0.0f, 1.0f}},
            {{2.0f, 0.5f, 1.0f},    {0.0f, 0.5f, 0.0f}},
            {{2.0f, 0.5f, -1.0f},   {0.5f, 0.0f, 0.5f}},
    };

    GLuint *anotherCubeIndiciesData = new GLuint[anotherCubeTotalIndicies]{
            0, 1, 2,        //first triangle
            1, 2, 3,        //second triangle
            0, 1, 4,        //third triangle
            1, 4, 5,        //fourth triangle
            4, 5, 6,        //fifth triangle
            5, 6, 7,        //sixth triangle
            2, 3, 6,        //seventh triangle
            3, 6, 7,        //eight triangle
            0, 2, 4,        //ninth triangle
            2, 4, 6,        //tenth triangle
            1, 3, 5,        //eleventh triangle
            3, 7, 5,        //twelfth triangle
    };




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


    entities.push_back(new Entity(cubeVerticiesData, cubeTotalVerticies,
                                  cubeIndiciesData, cubeTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    entities.push_back(new Entity(groundVerticiesData, groundTotalVerticies,
                                  groundIndiciesData, groundTotalIndicies,
                                  "../src/shader/GLSL/vertexShaderSource1.glslv",
                                  "../src/shader/GLSL/fragmentShaderSource1.glslf"));

    entities.push_back(new Entity(anotherCubeVerticiesData, anotherCubeTotalVerticies,
                                  anotherCubeIndiciesData, anotherCubeTotalIndicies,
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

//        entities[0]->getTransformation().translate(glm::vec3(0.0f, -0.001f, 0.0f));
//        entities[0]->getTransformation().modelLocation(entities[0]->getShader().ProgramID());

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



//~Entity::Entity()
//{
//
//}





































