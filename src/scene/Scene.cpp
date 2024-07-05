#include "Scene.hpp"
#include "../debug/LOG.hpp"
#include "../window/Window.hpp"
#include "../utils/RunParallel.hpp"
#include "../math/Transformation.hpp"
#include "../audio/Audio.hpp"

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


void Scene::Init()
{
    m_modelLoader = new ModelLoader();
    m_modelLoader->SetModelsDataMap();
    physics = new Physics();

    //SetModelsMapData();
    this->LoadRenderableObjectsStatically();
}


void Scene::LoadRenderableObjectsStatically()
{
    //namespace data = modelsData;




    constexpr std::size_t initialSceneObjects = 6;
//    //will replace 'GetModel' function with an unordered map
//    m_renderableObjects.push_back(new RenderableObject(GetModel<float>("Cube")));
//    m_renderableObjects.push_back(new RenderableObject(GetModel<float>("Ground")));
//    m_renderableObjects.push_back(new RenderableObject(GetModel<float>("Trapizoid")));
//    m_renderableObjects.push_back(new RenderableObject(GetModel<float>("Pyramid")));
//    m_renderableObjects.push_back(new RenderableObject(GetModel<float>("Cylinder")));
//    m_renderableObjects.push_back(new RenderableObject(GetModel<float>("Icosphere")));
//    m_renderableObjects.push_back(new RenderableObject(GetModel<float>("Sphere")));

    std::vector<std::string> modelsName{"Cube", "Trapizoid", "Pyramid", "Cylinder", "Icosphere", "Sphere"};

    glm::vec3 positions[initialSceneObjects] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(9.0f, 3.0f, 9.0f),
            glm::vec3(10.0, 10.0f, 30.0f),
            glm::vec3(10.0f, 0.0f, 10.0f),
            glm::vec3(9.0f, 0.0f, 0.0f)
    };

    std::cout << "Is Loading?" << '\n';

    for(std::size_t i=0; i<initialSceneObjects; ++i) [[likely]]
    {
        m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel(modelsName[i]), "../vendor/imageLoader/groundTexture.jpg"));
        //m_renderableObjects.push_back(new RenderableObject(GetMeshes(modelsName[i])));
        std::cout << "Is static scene loader going to crash!" << '\n';
        m_renderableObjects[i]->m_position = positions[i];
    }


    constexpr signed int initialGrounds = 5;
    constexpr signed int initialNegGrounds = -5;

    //#pragma omp parallel for
    for(signed int j=initialNegGrounds; j<initialGrounds; ++j)
    {
        //#pragma omp parallel for
        for(signed int i=initialNegGrounds; i<initialGrounds; ++i)
        {
            m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Ground"), "../vendor/imageLoader/clearRoadTexture.jpg"));
            std::size_t lastEntityIndex = m_renderableObjects.size()-1;
            m_renderableObjects[lastEntityIndex]->m_position = glm::vec3(j*(20.0f), -1.0f, i*(20.0f));
        }
    }


//    const std::size_t totalCurrentObjects = m_renderableObjects.size();
//    constexpr std::size_t totalBatchObjects = 1;
//    const std::size_t iteratorEdge = totalBatchObjects + totalCurrentObjects;
//    for(std::size_t i=totalCurrentObjects-1; i<iteratorEdge; ++i)
//    {
//        m_renderableObjects.push_back(new RenderableObject(GetModel<float>(modelsName[6])));
//        m_renderableObjects[i]->m_position.x = rand() % 100;
//        m_renderableObjects[i]->m_position.y = rand() % 100;
//        m_renderableObjects[i]->m_position.z = rand() % 100;
//    }




//    omp_set_num_threads(0x8);
//    #pragma omp parallel for  //if there are small amount of objects then using pragma won't result the expected
    for(RenderableObject *renderableObject: m_renderableObjects) [[likely]]
    {
        renderableObject->LoadVertexObjects(8, true); //if we add texture then it will be 8
        renderableObject->LoadTexture();
        //renderableObject->LoadMeshes();
    }

}



void Scene::CreateRenderableObject(const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch)
{
    Synapse::Audio *audio = new Synapse::Audio();
    audio->Play("../vendor/bell.wav");

    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Sphere"), "../vendor/imageLoader/basketballTexture.jpg"));
    //this->AddRenderableObject("Sphere", "../vendor/imageLoader/basketballTexture.jpg");
    //m_renderableObjects.push_back(new RenderableObject(GetMeshes("Sphere")));

    std::size_t lastEntityIndex = m_renderableObjects.size()-1;

    //check if the currently loaded renderable object is empty or not
    if(m_renderableObjects[lastEntityIndex]->GetTotalIndicies() == 0)
    {
        m_renderableObjects.pop_back();
    }

    m_renderableObjects[lastEntityIndex]->LoadVertexObjects(8, true); //if we add texture then it will be 8
    m_renderableObjects[lastEntityIndex]->LoadTexture();
    //camera's target position is only targetting at -z
    float zToShift = -5.0f;

    //m_renderableObjects[lastEntityIndex]->Translate(currentCameraTargetPos + glm::vec3(0.0f, 0.0f, zToShift));
    m_renderableObjects[lastEntityIndex]->m_position += currentCameraTargetPos + glm::vec3(0.0f, 0.0f, zToShift);
    //the model matrix will be modified using 'SendMatrix4ToGPU()'

    glm::vec3 velocity = currentCameraTargetPos - cameraPos;    //don't need to normalize if we access the front vector

    m_renderableObjects[lastEntityIndex]->m_velocity.x = velocity.x;
    m_renderableObjects[lastEntityIndex]->m_velocity.z = velocity.z;

    m_renderableObjects[lastEntityIndex]->m_initialVelocity = m_renderableObjects[lastEntityIndex]->m_velocity;
    m_renderableObjects[lastEntityIndex]->m_initialVelocity.y = glm::abs(cameraPos.y) * 0.1f; //here cameras direction vectors 'y' component also matters

    delete audio;
}




void Scene::LoadRenderableObjectDynamically(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch)
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
        this->CreateRenderableObject(currentCameraTargetPos, cameraPos, yaw, pitch);
    }

}



void Scene::RemoveRenderableObjectDynamically(GLFWwindow *window)
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



void Scene::RenderableObjectKeyboardMovement(GLFWwindow *window, std::size_t index)
{
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, 1.0f/10.0f, 0.0f));
        m_renderableObjects[index]->m_position.y += 1.0f/10.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, -1.0f/10.0f, 0.0f));
        m_renderableObjects[index]->m_position.y -= 1.0f/10.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(1.0f/10.0f, 0.0f, 0.0f));
        m_renderableObjects[index]->m_position.x += 1.0f/10.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(-1.0f/10.0f, 0.0f, 0.0f));
        m_renderableObjects[index]->m_position.x -= 1.0f/10.0f;
    }
}


void Scene::Update(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch, float deltaTime)
{
    if(m_renderableObjects.size() <= 0)
    {
        return;
    }

    //these will be inside the 'EntityLoader' class(maybe)
    this->LoadRenderableObjectDynamically(window, currentCameraTargetPos, cameraPos, yaw, pitch);
    this->RemoveRenderableObjectDynamically(window);

    std::size_t lastEntityIndex = m_renderableObjects.size()-1;

#define __APPLY__PHYSICS__
#ifdef __APPLY__PHYSICS__

    //m_renderableObjects[0]->m_position.z += 0.01f;
    //m_renderableObjects[6]->Rotate(1.0f, glm::vec3(0.0f, -1.0f, 0.0f));

    std::cout << "Radius of rotation: " << glm::length(m_renderableObjects[6]->m_position) << '\n';



    float deltaTime2 = 0.27f;    //here made an approximate delta time for this device. will calculate deltaTime

    //float groundVerticalDistance = m_renderableObjects[1]->m_position.y;
    float groundVerticalDistance = 0.0f;
    //#pragma omp parallel for
    for (std::size_t i = 6; i < m_renderableObjects.size(); ++i)
    {
        physics->Projectile(m_renderableObjects[i]->m_position, m_renderableObjects[i]->m_velocity, deltaTime2, m_renderableObjects[i]->m_initialVelocity, true, true, groundVerticalDistance);
        //physics->OrbitAround(m_renderableObjects[i]->m_position, m_renderableObjects[0]->m_position, m_theta);    //right now it's orbiting the origin
        //m_renderableObjects[i]->Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        //TransformComponent::Translate(m_renderableObjects[i], glm::vec3(0.0, 10.0f, 0.0f));
    }

    m_theta += 0.1f;

#endif

    this->RenderableObjectKeyboardMovement(window, lastEntityIndex);

//    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//    {
//        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, 1.0f/10.0f, 0.0f));
//        m_renderableObjects[lastEntityIndex]->m_position.y += 1.0f/10.0f;
//    }
//
//    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//    {
//        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, -1.0f/10.0f, 0.0f));
//        m_renderableObjects[lastEntityIndex]->m_position.y -= 1.0f/10.0f;
//    }
//
//    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//    {
//        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(1.0f/10.0f, 0.0f, 0.0f));
//        m_renderableObjects[lastEntityIndex]->m_position.x += 1.0f/10.0f;
//    }
//
//    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//    {
//        //m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(-1.0f/10.0f, 0.0f, 0.0f));
//        m_renderableObjects[lastEntityIndex]->m_position.x -= 1.0f/10.0f;
//    }


    std::cout << "Total renderable objects: " << m_renderableObjects.size() << '\n';    //this is causing crash
    std::cout << "Completed updating current scene!" << '\n';
}




Scene::~Scene()
{
    delete m_modelLoader;
    delete physics;
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








