#include "Scene.hpp"
#include "../debug/LOG.hpp"
#include "../window/Window.hpp"
#include "ModelsData.hpp"
#include "../utils/RunParallel.hpp"


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <math.h>
#include <random>


#define __RELEASE__
//#define __DEBUG__


#if defined(__RELEASE__)
    #define __UTILIZE__BRANCHPREDICTION__
    #define __RUNTIME__MULTITHREADING__
    //#define __LOADTIME__MULTITHREADING__
#elif defined(__DEBUG__)
    #define __SINGLETHREADING__
#endif


namespace Synapse
{



//inline std::unordered_map<std::string, Model> model = {{"Cube", Model(modelsData::cubeVerticiesData, modelsData::cubeTotalVerticies, modelsData::cubeIndiciesData, modelsData::cubeTotalIndicies)}};





void Scene::Init()
{
    this->LoadRenderableObjectsStatically();
}


void Scene::LoadRenderableObjectsStatically()
{
    namespace data = modelsData;

#if 1

    m_renderableObjects.push_back(new RenderableObject(GetModel("Cube")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Ground")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Trapizoid")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Pyramid")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Cylinder")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Icosphere")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Sphere")));


    glm::vec3 positions[7] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, -0.9f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(9.0f, 3.0f, 9.0f),
            glm::vec3(10.0, 10.0f, 30.0f),
            glm::vec3(10.0f, 0.0f, 10.0f),
            glm::vec3(9.0f, 0.0f, 0.0f)
    };

    for(std::size_t i=0; i<m_renderableObjects.size(); ++i) [[likely]]
    {
        m_renderableObjects[i]->m_position = positions[i];
    }


//    m_renderableObjects[6]->m_position = m_renderableObjects[4]->m_position;
//    m_renderableObjects[6]->m_position.x -= 3.0f;
//    m_renderableObjects[6]->m_position.z -= 3.0f;


    std::vector<std::string> modelsName{"Cube", "Trapizoid", "Pyramid", "Cylinder", "Icosphere", "Sphere"};


//    const std::size_t totalCurrentObjects = m_renderableObjects.size();
//    constexpr std::size_t totalBatchObjects = 1;
//    const std::size_t iteratorEdge = totalBatchObjects + totalCurrentObjects;
//    for(std::size_t i=totalCurrentObjects-1; i<iteratorEdge; ++i)
//    {
//        m_renderableObjects.push_back(new RenderableObject(GetModel(modelsName[5])));
//        m_renderableObjects[i]->m_position.x = rand() % 10;
//        m_renderableObjects[i]->m_position.y = rand() % 10;
//        m_renderableObjects[i]->m_position.z = rand() % 10;
//    }




#else

    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[0]->SetName("Light Source");
    m_renderableObjects[0]->SetVerticies(data::cubeTotalVerticies, data::cubeVerticiesData);
    m_renderableObjects[0]->SetIndicies(data::cubeTotalIndicies, data::cubeIndiciesData);
    m_renderableObjects[0]->m_position = glm::vec3(10.0f, 5.0f, 0.0f);



    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[1]->SetName("Ground");
    m_renderableObjects[1]->SetVerticies(data::groundTotalVerticies, data::groundVerticiesData);
    m_renderableObjects[1]->SetIndicies(data::groundTotalIndicies, data::groundIndiciesData);
    m_renderableObjects[1]->m_position = glm::vec3(0.0f, 0.0f, 0.0f);



    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[2]->SetName("3D Trapizium");
    m_renderableObjects[2]->SetVerticies(data::trapizoidTotalVerticies, data::trapizoidVerticiesData);
    m_renderableObjects[2]->SetIndicies(data::trapizoidTotalIndicies, data::trapizoidIndiciesData);
    m_renderableObjects[2]->m_position = glm::vec3(1.0f, 0.0f, 0.0f);



    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[3]->SetName("Pyramid");
    m_renderableObjects[3]->SetVerticies(data::pyramidTotalVerticies, data::pyramidVerticesData);
    m_renderableObjects[3]->SetIndicies( data::pyramidTotalIndicies, data::pyramidIndicesData);
    m_renderableObjects[3]->m_position = glm::vec3(9.0f, 3.0f, 9.0f);

#endif

//    omp_set_num_threads(0x8);
//    #pragma omp parallel for  //if there are small amount of objects then using pragma won't result the expected
    for(RenderableObject *renderableObject: m_renderableObjects) [[likely]]
    {
        renderableObject->LoadVertexObjects();
    }

}



void Scene::LoadRenderableObjectDynamically(const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch)
{
    m_renderableObjects.push_back(new RenderableObject(GetModel("Sphere")));
    std::size_t lastEntityIndex = m_renderableObjects.size()-1;
    m_renderableObjects[lastEntityIndex]->LoadVertexObjects();
    //camera's target position is only targetting at -z
    float zToShift = -5.0f;

    //m_renderableObjects[lastEntityIndex]->Translate(currentCameraTargetPos + glm::vec3(0.0f, 0.0f, zToShift));
    m_renderableObjects[lastEntityIndex]->m_position += currentCameraTargetPos + glm::vec3(0.0f, 0.0f, zToShift);
    //the model matrix will be modified using 'SendMatrix4ToGPU()'

    glm::vec3 velocity = currentCameraTargetPos - cameraPos;    //don't need to normalize if we access the front vector

    m_renderableObjects[lastEntityIndex]->m_velocity.x = velocity.x;
    m_renderableObjects[lastEntityIndex]->m_velocity.z = velocity.z;
}




void Scene::LoadRenderableObjectDynamicallyInput(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch)
{
    bool leftMouseButtonClicked = true;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
    {
        m_dynamicRenderableObjectLoaderRunning = false;
        leftMouseButtonClicked = false;
    }

    if (leftMouseButtonClicked && !m_dynamicRenderableObjectLoaderRunning)
    {
        m_dynamicRenderableObjectLoaderRunning = true;
        DEBUG::__LOG__MANAGER__::LOG("PRESSED Dynamic Entity Loader!");
        this->LoadRenderableObjectDynamically(currentCameraTargetPos, cameraPos, yaw, pitch);
    }

}

void Scene::RemoveRenderableObjectDynamicallyInput(GLFWwindow *window)
{
    bool rightMouseButtonClicked = true;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS)
    {
        m_dynamicRenderableObjectDeleterRunning = false;
        rightMouseButtonClicked = false;
    }

    if (rightMouseButtonClicked && !m_dynamicRenderableObjectDeleterRunning)
    {
        m_dynamicRenderableObjectDeleterRunning = true;
        DEBUG::__LOG__MANAGER__::LOG("PRESSED Dynamic Entity Deleter!");
        if (m_renderableObjects.size() > 0)
        {
            m_renderableObjects.pop_back();
        }
    }

}



//
//bool g_dynamicRenderableObjectLoaderRunning = false;
//bool g_dynamicRenderableObjectDeleterRunning = false;
//float g_theta = 0.0f;
//



//static void OrbitAround(glm::vec3 &renderableObjectsPosition, const glm::vec3 &positionToOrbit)
//{
//    //renderableObject->m_position.y += 1.0f/100.0f;
//    //renderableObject->Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//
////    float deltaX = renderableObject->m_position.x - positionToOrbit.x;
////    float deltaZ = renderableObject->m_position.z - positionToOrbit.z;
//
////    std::cout << "Delta X: " << deltaX << '\n';
////    std::cout << "Delta Z: " << deltaZ << '\n';
//
//    //float r = glm::sqrt(deltaX*deltaX + deltaZ*deltaZ);
//    float r = 3.0f;
//    std::cout << "Radius: " << r << '\n';
//
//
//    //renderableObject->m_position.y += 1.0f/100.0f;
//
//    renderableObjectsPosition.x = r * glm::cos(g_theta);
//    renderableObjectsPosition.z = r * glm::sin(g_theta);
//
//    std::cout << "X pos: " << renderableObjectsPosition.x << '\n';
//    std::cout << "Z pos: " << renderableObjectsPosition.z << '\n';
//
//    std::cout << "Theta: " << g_theta << '\n';
//
//    g_theta += 0.1f;
//}





void Scene::Update(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch)
{
    if(m_renderableObjects.size() < 0)
    {
        return;
    }

    //these will be inside the 'EntityLoader' class(maybe)
    this->LoadRenderableObjectDynamicallyInput(window, currentCameraTargetPos, cameraPos, yaw, pitch);
    this->RemoveRenderableObjectDynamicallyInput(window);



    //m_renderableObjects[0]->m_position.z += 0.01f;
    //m_renderableObjects[6]->Rotate(1.0f, glm::vec3(0.0f, -1.0f, 0.0f));

    std::cout << "Radius of rotation: " << glm::length(m_renderableObjects[6]->m_position) << '\n';

    std::size_t lastEntityIndex = m_renderableObjects.size()-1;


    float deltaTime = 0.27f;    //here made an approximate delta time for this device. will calculate deltaTime

    //#pragma omp parallel for
    for (std::size_t i = 6; i < m_renderableObjects.size(); ++i)
    {
        physics->Projectile(m_renderableObjects[i]->m_position, m_renderableObjects[i]->m_velocity, deltaTime);
        //physics->OrbitAround(m_renderableObjects[i]->m_position, m_renderableObjects[0]->m_position, m_theta);    //right now it's orbiting the origin
    }

    m_theta += 0.1f;


    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, 1.0f/10.0f, 0.0f));
        m_renderableObjects[lastEntityIndex]->m_position.y += 1.0f/10.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, -1.0f/10.0f, 0.0f));
        m_renderableObjects[lastEntityIndex]->m_position.y -= 1.0f/10.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(1.0f/10.0f, 0.0f, 0.0f));
        m_renderableObjects[lastEntityIndex]->m_position.x += 1.0f/10.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(-1.0f/10.0f, 0.0f, 0.0f));
        m_renderableObjects[lastEntityIndex]->m_position.x -= 1.0f/10.0f;
    }



    std::cout << "Total renderable objects: " << m_renderableObjects.size() << '\n';    //this is causing crash


#undef __RUNTIME__MULTITHREADING__
#define __SINGLETHREADING__
#ifdef __RUNTIME__MULTITHREADING__
    unsigned short threadsToUtilize = 0x5;
    //even ther if given '1, 2' instead of '0' when the total renderable objects are '3', it still works fine.
    //probably the same error as said previously in the 'LoadRenderableObjectsStatically()'
    //will fix this error.
    Threading::S_pragma_omp_parallel_loop<void, std::size_t>(0, m_renderableObjects.size(), threadsToUtilize,
    [this](auto i) -> void
    {
        m_renderableObjects[i]->Update();
    });
#elif defined(__SINGLETHREADING__)
    for(RenderableObject *renderableObject : m_renderableObjects)
    {
        break;
        //renderableObject->Update();
    }
#endif


    std::cout << "Completed updating current scene!" << '\n';


}




Scene::~Scene()
{
    for(std::size_t i=0; i<m_renderableObjects.size(); ++i)
    {
        break;
    }
}


#if defined(__RELEASE__)
    #undef __RELEASE__
    #undef __UTILIZE__BRANCHPREDICTION__
    #undef __RUNTIME__MULTITHREADING__
    //#undef __LOADTIME__MULTITHREADING__
#elif defined(__DEBUG__)
    #undef __DEBUG__
    #undef __SINGLETHREADING__
#endif



}   //namespace 'Synapse'








