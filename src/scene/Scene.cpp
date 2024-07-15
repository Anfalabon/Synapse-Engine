#include "Scene.hpp"
#include "debug/LOG.hpp"
#include "window/Window.hpp"
#include "core/RunParallel.hpp"
#include "math/Transformation.hpp"
#include "core/MemoryManager.hpp"
#include "core/Benchmark.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <math.h>
#include <random>
#include <climits>




namespace Synapse
{


void Scene::Init()
{

    m_modelLoader = new Synapse::ModelLoader();
    m_modelLoader->SetModelsDataMap();
    m_physics = new Synapse::Physics();

    this->LoadInitialRenderableObjects();

}


//static void Quaternions(float theta, const glm::vec3 &axisOfRotation, glm::vec3 &position)
//{
//    theta = glm::radians(theta);
//
//    float w = glm::cos(theta/2);
//    float x = axisOfRotation.x * glm::sin(theta/2);
//    float y = axisOfRotation.y * glm::sin(theta/2);
//    float z = axisOfRotation.z * glm::sin(theta/2);
//
//    glm::vec4 qPosition = glm::vec4(0, position.x , position.y, position.z);
//    glm::vec4 q = glm::vec4(w, x, y, z);
//    glm::vec4 qDash = glm::vec4(w, -1.0f*x, -1.0f*y, -1.0f*z);
//
//    glm::vec4 rotatedPoint = q * qPosition * qDash;
//
//    position.x = rotatedPoint.x;
//    position.y = rotatedPoint.y;
//    position.z = rotatedPoint.z;
//}


void Scene::LoadInitialRenderableObjects()
{
    //namespace data = modelsData;




    constexpr std::size_t initialSceneObjects = 7;

    std::vector<std::string> modelsName{"Cube", "Trapizoid", "Pyramid", "Cylinder", "Icosphere", "Black Hole", "Wall"};

    glm::vec3 positions[initialSceneObjects] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(9.0f, 3.0f, 9.0f),
            glm::vec3(10.0, 10.0f, 30.0f),
            glm::vec3(10.0f, 0.0f, 10.0f),
            glm::vec3(100.0f, 0.0f, 100.0f),
            glm::vec3(0.0f, -1.0f, 0.0f)
    };

    std::cout << "Is Loading?" << '\n';




    for(std::size_t i=0; i<initialSceneObjects; ++i) [[likely]]
    {
        DEBUG("Initializing the initial scene objects...");
        m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel(modelsName[i])));
        //this->AddRenderableObject(modelsName[i]);
        std::cout << "Is static scene loader going to crash!" << '\n';
        m_renderableObjects[i]->m_position = positions[i];
        std::cout << "Created an object successfully!" << '\n';
    }




    float tempZ = m_renderableObjects[5]->m_position.z;
    m_theta = 45.0f;
    m_theta = glm::radians(m_theta);
    m_renderableObjects[5]->m_position.z = glm::cos(m_theta)*m_renderableObjects[5]->m_position.z - glm::sin(m_theta)*m_renderableObjects[5]->m_position.y;
    m_renderableObjects[5]->m_position.y = glm::sin(m_theta)*tempZ + glm::cos(m_theta)*m_renderableObjects[5]->m_position.y;



    std::cout << "Black Hole z pos: " << m_renderableObjects[5]->m_position.z << '\n';
    std::cout << "Black Hole y pos: " << m_renderableObjects[5]->m_position.y << '\n';
    std::cout << "Angle: " << m_theta << '\n';

    std::cout << "Lenght of Black Hole's rotation vector: " << glm::length(m_renderableObjects[5]->m_position) << '\n';



#if 1

    DEBUG("Walls loading...");
    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Wall")));
    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Wall")));
    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Wall")));
    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Door")));

//    this->AddRenderableObject("Wall");
//    this->AddRenderableObject("Wall");
//    this->AddRenderableObject("Wall");
//    this->AddRenderableObject("Door");



    m_renderableObjects[7]->m_position.x -= 14.86f;
    m_renderableObjects[7]->m_position.y -= 1.0f;
    m_renderableObjects[7]->m_position.z += 10.0f;
    m_renderableObjects[7]->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    //m_renderableObjects[7]->Translate(glm::vec3(-14.86f, -1.0f, 10.0f));



    m_renderableObjects[8]->m_position.x -= 0.0f;
    m_renderableObjects[8]->m_position.y -= 1.0f;
    m_renderableObjects[8]->m_position.z += 20.0f;


    m_renderableObjects[9]->m_position.y += 1.0f;
    m_renderableObjects[9]->m_position.z += 100.0f;
    //m_renderableObjects[9]->Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    m_renderableObjects[10]->m_position.x -= 14.86f;
    m_renderableObjects[10]->m_position.y -= 1.0f;
    m_renderableObjects[10]->m_position.z -= 10.0f;
    m_renderableObjects[10]->Scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_renderableObjects[10]->Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

#endif


#if 1
    constexpr signed int initialGrounds = 10;
    constexpr signed int initialNegGrounds = -1;

    //#pragma omp parallel for
    for(signed int j=initialNegGrounds; j<initialGrounds; ++j)
    {
        //#pragma omp parallel for
        for(signed int i=initialNegGrounds; i<initialGrounds; ++i)
        {
            //m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Ground"), "../vendor/imageLoader/clearRoadTexture.jpg"));
            m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Ground")));
            std::size_t lastEntityIndex = m_renderableObjects.size()-1;
            m_renderableObjects[lastEntityIndex]->m_position = glm::vec3(j*(20.0f), -1.0f, i*(20.0f));
        }
    }
#endif

//    minX = -20.0f;
//    maxX = 180.0f;

//    minZ = -20.0f;
//    maxX = 180.0f;


    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Camera")));

    {
        std::size_t lastEntityIndex = m_renderableObjects.size()-1;
        m_firstCameraIndex = lastEntityIndex;
    }

    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Camera")));
    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Camera")));


    //m_renderableObjects[m_firstCameraIndex]->m_position = glm::vec3(10.0f, 10.0f,10.0f);


    //m_renderableObjects.push_back(new Player(m_modelLoader->GetModel("Male")));
    //m_renderableObjects.push_back(new NonPlayableCharacter(m_modelLoader->GetModel("Male")));

    for(RenderableObject *renderableObject: m_renderableObjects) [[likely]]
    {
        renderableObject->LoadMeshes();
        //renderableObject->LoadVertexObjects(8, true); //if we add texture then it will be 8
        //renderableObject->LoadTexture();
    }

}



void lm()
{
    std::cin.get();
}



void Scene::CreateRenderableObject(Synapse::Camera *camera)
{

    m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel("Sphere")));

    std::size_t lastEntityIndex = m_renderableObjects.size()-1;

    //check if the currently loaded renderable object is renderable or not
    if(m_renderableObjects[lastEntityIndex]->GetTotalIndiciesOfMesh(0) == 0)
    {
        m_renderableObjects.pop_back();
        return;
    }

    std::cout << "Total renderable objects2: " << m_renderableObjects.size() << '\n';    //this is causing crash

    m_renderableObjects[lastEntityIndex]->LoadMeshes();
    //m_renderableObjects[lastEntityIndex]->Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec3 scaledFrontVector = 3.0f * camera->GetFrontVector();   //scale the direction vector

    m_renderableObjects[lastEntityIndex]->m_position = scaledFrontVector;  //first assign it's position to the scaled normalized direction vector
    m_renderableObjects[lastEntityIndex]->m_position += camera->GetPos();   //then translate it the position of Camera's current position

    //the model matrix will be modified using 'SendMatrix4ToGPU()'

    glm::vec3 velocity = camera->GetFrontVector();

    m_renderableObjects[lastEntityIndex]->m_velocity.x = velocity.x;
    m_renderableObjects[lastEntityIndex]->m_velocity.z = velocity.z;

    m_renderableObjects[lastEntityIndex]->m_initialVelocity = m_renderableObjects[lastEntityIndex]->m_velocity;
    m_renderableObjects[lastEntityIndex]->m_initialVelocity.y = glm::abs(camera->GetPos().y) * 0.1f; //here cameras direction vectors 'y' component also matters

}




void Scene::LoadRenderableObjectDynamically(GLFWwindow *window, Synapse::Camera *camera)
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
        this->CreateRenderableObject(camera);
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



static std::size_t SelectObjectByIndex(GLFWwindow *window)
{

    for(std::size_t i=0; i<10; ++i)
    {
        if(glfwGetKey(window, GLFW_KEY_0 + i) == GLFW_PRESS)
        {
            return (GLFW_KEY_0 + i);
        }
    }

}


static bool keepingLeftMouseButtonHolding(GLFWwindow *window)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        return true;
    }
    return false;
}



void Scene::RenderableObjectKeyboardMovement(GLFWwindow *window, std::size_t index)
{
    //index = SelectObjectByIndex(window);

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


float g_angleRotated = 0.0f;
bool  g_stopRotating = false;



int64_t Scene::RenderableObjectCameraLookingAt(Synapse::Camera *camera)
{
    std::size_t currentRenderableObjectIndex = 0;

    glm::vec3 distanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 directionVector = 3.0f * camera->GetFrontVector();    //here directionVector length will be always '3.0f'
    glm::vec3 cameraPos = camera->GetPos();


    float minDistance = glm::length(cameraPos - m_renderableObjects[0]->m_position);


    //find the renderable object which distance vector length is minimum
    for(std::size_t i=0; i<m_renderableObjects.size(); ++i)
    {
        distanceVector = cameraPos - m_renderableObjects[i]->m_position;
        float distanceLength = glm::length(distanceVector);
        if(distanceLength < minDistance)
        {
            minDistance = distanceLength;
            currentRenderableObjectIndex = i;
        }



    }

    float length2 = glm::length(directionVector);
    //directionVector += camera->GetPos();

    if((glm::dot(distanceVector, directionVector) == minDistance * length2) || (minDistance <= length2))
    {
        lookingAtRenderableObject = true;
        return (int64_t)currentRenderableObjectIndex;
    }

    return -1;
}



void Scene::SelectRenderableObject(GLFWwindow *window, Synapse::Camera *camera)
{
    bool holdingLeftMouseButton = false;
    int64_t index = -1;

    if(!keepingLeftMouseButtonHolding(window))
    {
        lookingAtRenderableObject = false;
    }
    else
    {
        holdingLeftMouseButton = true;
        index = this->RenderableObjectCameraLookingAt(camera);
        std::cout << "Selected Renderable Object Index: " << index << '\n';
        if(index < 0)
        {
            lookingAtRenderableObject = false;
        }
    }

    if(holdingLeftMouseButton && lookingAtRenderableObject)
    {
        glm::vec3 translatedDirectionVector = 3.0f * camera->GetFrontVector();
        translatedDirectionVector += camera->GetPos();
        m_renderableObjects[index]->m_position = std::move(translatedDirectionVector);
    }
}







void Scene::SelectRenderableObjectTemp(GLFWwindow *window, Synapse::Camera *camera, const char &)
{
    std::size_t currentRenderableObjectIndex = 2;

    glm::vec3 directionVector = 6.0f * camera->GetFrontVector();

    float length2 = glm::length(directionVector);

    directionVector += camera->GetPos();


    glm::vec3 Vec1 = m_renderableObjects[currentRenderableObjectIndex]->m_position;
    glm::vec3 Vec2 = camera->GetPos();
    glm::vec3 distanceVector = Vec2 - Vec1;

    float length1 = glm::length(distanceVector);


    //DEBUG::__LOG__MANAGER__::GLM_LOG();

    float dotProduct = glm::dot(distanceVector, directionVector);
    float lengthsProduct = length1 * glm::length(directionVector);

    float angle = glm::degrees(glm::acos(dotProduct/lengthsProduct));
    //glm::dot(distanceVector, directionVector) == length1 * length2)


    std::cout << "Angle: " << angle << '\n';

    if(glm::abs(angle) < 90.0f && (length1 <= length2))
    {
        lookingAtRenderableObject = true;
    }

    bool holdingLeftMouseButton = false;

    if(!keepingLeftMouseButtonHolding(window))
    {
        lookingAtRenderableObject = false;
    }
    else
    {
        holdingLeftMouseButton = true;
    }


    if(holdingLeftMouseButton && lookingAtRenderableObject)
    {
        DEBUG("Renderable object to choose: ");
        ////////////////////////////////here multiply the front vector by 'm_physics->m_speedCoefficiet'
        m_renderableObjects[currentRenderableObjectIndex]->m_position = std::move(directionVector);
        std::cout << currentRenderableObjectIndex << '\n';
    }

}




void Scene::KeepRenderableObjectsUnderBoundry()
{
//    for(std::size_t i=0; i<m_renderableObjects.size(); ++i)
//    {
//        if(i != m_firstCameraIndex + 0 && i != m_firstCameraIndex + 1 && i != m_firstCameraIndex + 2)
//        {
//            glm::vec3 pos = m_renderableObjects[i]->m_position;
//            bool isInsideGroundRegion = false;
//            if(pos.x >= -20.0f && pos.x <= 180.0f &&
//               pos.z >= -20.0f && pos.z <= 180.0f)
//            {
//                //S_PAUSE_FOR_READING();
//                DEBUG("Inside the Ground Region!");
//                isInsideGroundRegion = true;
//            }
//
//            if(!isInsideGroundRegion)
//            {
//                float gravity = -0.1f;
//                float deltaTime = 0.27f;
//                m_renderableObjects[i]->m_position.y += m_renderableObjects[i]->m_velocity.y * deltaTime;
//                m_renderableObjects[i]->m_velocity.y += gravity * deltaTime;
//            }
//        }
//    }


    for(std::size_t i=0; i<m_renderableObjects.size(); ++i)
    {
        if(i != m_firstCameraIndex + 0 && i != m_firstCameraIndex + 1 && i != m_firstCameraIndex + 2)
        {
            m_physics->KeepUnderBoundry(glm::vec3(-20.0f, -1000000000, -20.0f),
                                        glm::vec3(180.0f, 1000000000, 180.0f),
                                        m_renderableObjects[i]->m_position,
                                        m_renderableObjects[i]->m_velocity);
        }
    }

}



__ALWAYS__INLINE__ static bool IsInsideBoundry(const glm::vec3 &pos, const glm::vec3 &boundryMinLimit, const glm::vec3 &boundryMaxLimit)
{
    return (pos.x >= boundryMinLimit.x && pos.x <= boundryMaxLimit.x &&
            pos.y >= boundryMinLimit.y && pos.y <= boundryMaxLimit.y &&
            pos.z >= boundryMinLimit.z && pos.z <= boundryMaxLimit.z);
}


//void Scene::Update(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch, float deltaTime)
void Scene::Update(GLFWwindow *window, Synapse::Camera *camera, std::size_t currentCameraIndex, float deltaTime)
{
    if(m_renderableObjects.size() <= 0)
    {
        return;
    }

    //these will be inside the 'EntityLoader' class(maybe)


    this->LoadRenderableObjectDynamically(window, camera);
    this->RemoveRenderableObjectDynamically(window);

#if 0
    this->SelectRenderableObject(window, camera);
#else
    this->SelectRenderableObjectTemp(window, camera, 'c');
#endif

    this->KeepRenderableObjectsUnderBoundry();


    //m_scriptingEngine->AddData<float>();


    //m_renderableObjects[m_firstCameraIndex + currentCameraIndex]->m_position = camera->GetPos();
    //m_renderableObjects[m_firstCameraIndex + currentCameraIndex]->m_position.z -= 2.0f;


    std::size_t lastEntityIndex = m_renderableObjects.size()-1;

#define __APPLY__PHYSICS__
#ifdef __APPLY__PHYSICS__


    std::cout << "Radius of rotation: " << glm::length(m_renderableObjects[6]->m_position) << '\n';

    //Quaternions(90.0f, glm::vec3(1.0f, 0.0f, 0.0f), m_renderableObjects[7]->m_position);


    float deltaTime2 = 0.27f;    //here made an approximate delta time for this device. will calculate deltaTime

    //float groundVerticalDistance = m_renderableObjects[1]->m_position.y;
    float groundVerticalDistance = 0.0f;
    //#pragma omp parallel for
    for (std::size_t i = 6; i < m_renderableObjects.size(); ++i)
    {
        if(i != m_firstCameraIndex + 0 && i != m_firstCameraIndex + 1 && i != m_firstCameraIndex + 2)
        {
            if(IsInsideBoundry(m_renderableObjects[i]->m_position, glm::vec3(-20.0f, -1000000000, -20.0f) , glm::vec3(180.0f, 1000000000, 180.0f)))
            {
                m_physics->Projectile(m_renderableObjects[i]->m_position, m_renderableObjects[i]->m_velocity, deltaTime2, m_renderableObjects[i]->m_initialVelocity, true, true, groundVerticalDistance);
            }
        }
        //physics->OrbitAround(m_renderableObjects[i]->m_position, m_renderableObjects[0]->m_position, m_theta);    //right now it's orbiting the origin
        //m_renderableObjects[i]->Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        //m_renderableObjects[i]->Rotate(1.0f, true, false, true);
        //TransformComponent::Translate(m_renderableObjects[i], glm::vec3(0.0, 10.0f, 0.0f));
    }

    //m_renderableObjects[10]->Rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));



    //m_theta += 0.01f;


#endif

    this->RenderableObjectKeyboardMovement(window, lastEntityIndex);


    std::cout << "Total renderable objects: " << m_renderableObjects.size() << '\n';    //this is causing crash
    std::cout << "Completed updating current scene!" << '\n';

}



void Scene::Clear()
{
    MemoryManager::Clean<Synapse::ModelLoader>(m_modelLoader);
    MemoryManager::Clean<Synapse::Physics>(m_physics);

    m_wasClearMethodCalled = true;
}


//may cause error if 'Clear()' is already called for cleaning up all the memories allocated by Scene object
Scene::~Scene()
{
    if(!m_wasClearMethodCalled)
    {
        MemoryManager::Clean<Synapse::ModelLoader>(m_modelLoader);
        MemoryManager::Clean<Synapse::Physics>(m_physics);
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








