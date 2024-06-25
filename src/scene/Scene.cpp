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

    m_renderableObjects.push_back(new RenderableObject(GetModel("Cube")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Ground")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Trapizoid")));
    m_renderableObjects.push_back(new RenderableObject(GetModel("Pyramid")));

    glm::vec3 positions[4] = {
            glm::vec3(10.0f, 5.0f, 0.0f),
            glm::vec3(0.0f, -10.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(9.0f, 3.0f, 9.0f)
    };


//    m_renderableObjects.push_back(new RenderableObject());
//    m_renderableObjects[0]->SetName("Light Source");
//    m_renderableObjects[0]->SetVerticies(data::cubeTotalVerticies, data::cubeVerticiesData);
//    m_renderableObjects[0]->SetIndicies(data::cubeTotalIndicies, data::cubeIndiciesData);
//    m_renderableObjects[0]->m_position = glm::vec3(10.0f, 5.0f, 0.0f);
//
//
//
//    m_renderableObjects.push_back(new RenderableObject());
//    m_renderableObjects[1]->SetName("Ground");
//    m_renderableObjects[1]->SetVerticies(data::groundTotalVerticies, data::groundVerticiesData);
//    m_renderableObjects[1]->SetIndicies(data::groundTotalIndicies, data::groundIndiciesData);
//    m_renderableObjects[1]->m_position = glm::vec3(0.0f, 0.0f, 0.0f);
//
//
//
//    m_renderableObjects.push_back(new RenderableObject());
//    m_renderableObjects[2]->SetName("3D Trapizium");
//    m_renderableObjects[2]->SetVerticies(data::trapizoidTotalVerticies, data::trapizoidVerticiesData);
//    m_renderableObjects[2]->SetIndicies(data::trapizoidTotalIndicies, data::trapizoidIndiciesData);
//    m_renderableObjects[2]->m_position = glm::vec3(1.0f, 0.0f, 0.0f);
//
//
//
//    m_renderableObjects.push_back(new RenderableObject());
//    m_renderableObjects[3]->SetName("Pyramid");
//    m_renderableObjects[3]->SetVerticies(data::pyramidTotalVerticies, data::pyramidVerticesData);
//    m_renderableObjects[3]->SetIndicies( data::pyramidTotalIndicies, data::pyramidIndicesData);
//    m_renderableObjects[3]->m_position = glm::vec3(9.0f, 3.0f, 9.0f);


    for(std::size_t i=0; i<m_renderableObjects.size(); ++i) [[likely]]
    {
        m_renderableObjects[i]->m_position = positions[i];
    }

    for(RenderableObject *renderableObject: m_renderableObjects) [[likely]]
    {
        renderableObject->LoadVertexObjects();
    }


//    m_renderableObjects[0]->Update();
//    m_renderableObjects[0]->GetVA().Bind();
//    m_renderableObjects[0]->m_model = glm::translate(m_renderableObjects[0]->m_model, glm::vec3(0.0f, -1.0f, 0.0f));
//    m_renderableObjects[0]->GetShader().SendMatrix4ToGPU("model", m_renderableObjects[0]->m_model);

    //std::cin.get();

}



//have to fix and update this dynamic scene Loader which apparently doesn't work
void Scene::LoadRenderableObjectsDynamically(const glm::vec3 &currentCameraTargetPos)
{
    m_renderableObjects.push_back(new RenderableObject(GetModel("Pyramid")));
    std::size_t lastEntityIndex = m_renderableObjects.size()-1;
    m_renderableObjects[lastEntityIndex]->LoadVertexObjects();

    //camera's target position is only targetting at -z
    float zToShift = -2.0f;
    m_renderableObjects[lastEntityIndex]->Translate(currentCameraTargetPos + glm::vec3(0.0f, 0.0f, zToShift));

    //the model matrix will be modified using 'SendMatrix4ToGPU()'
}




bool g_dynamicRenderableObjectLoaderRunning = false;
bool g_dynamicRenderableObjectDeleterRunning = false;
float g_theta = 0.0f;
float g_tempTheta = 0.0f;
bool g_popBackDone = false;



static void OrbitAround(RenderableObject *renderableObject, const glm::vec3 &positionToOrbit)
{
    //renderableObject->m_position.y += 1.0f/100.0f;
    //renderableObject->Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

//    float deltaX = renderableObject->m_position.x - positionToOrbit.x;
//    float deltaZ = renderableObject->m_position.z - positionToOrbit.z;

//    std::cout << "Delta X: " << deltaX << '\n';
//    std::cout << "Delta Z: " << deltaZ << '\n';

    //float r = glm::sqrt(deltaX*deltaX + deltaZ*deltaZ);
    float r = 3.0f;
    std::cout << "Radius: " << r << '\n';


    //renderableObject->m_position.y += 1.0f/100.0f;
    renderableObject->m_position.x = r * glm::cos(g_theta);
    renderableObject->m_position.z = r * glm::sin(g_theta);


    std::cout << "X pos: " << renderableObject->m_position.x << '\n';
    std::cout << "Z pos: " << renderableObject->m_position.z << '\n';

    std::cout << "Theta: " << g_theta << '\n';

    g_theta += 0.01f;
}





void Scene::Update(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos)
{
    if(m_renderableObjects.size() < 0)
    {
        return;
    }

    //these will be inside the 'EntityLoader' class.

    //these will be inside some common function cause there logic is similar



    {

        bool leftMouseButtonClicked = true;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
        {
            g_dynamicRenderableObjectLoaderRunning = false;
            leftMouseButtonClicked = false;
        }

        if (leftMouseButtonClicked && !g_dynamicRenderableObjectLoaderRunning)
        {
            g_dynamicRenderableObjectLoaderRunning = true;
            DEBUG::__LOG__MANAGER__::LOG("PRESSED Dynamic Entity Loader!");
            this->LoadRenderableObjectsDynamically(currentCameraTargetPos);
//            if(g_popBackDone)
//            {
//                g_theta = g_tempTheta;
//                g_popBackDone = false;
//            }
        }

    }



    {

        bool rightMouseButtonClicked = true;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS)
        {
            g_dynamicRenderableObjectDeleterRunning = false;
            rightMouseButtonClicked = false;
        }

        if (rightMouseButtonClicked && !g_dynamicRenderableObjectDeleterRunning)
        {
            g_dynamicRenderableObjectDeleterRunning = true;
            DEBUG::__LOG__MANAGER__::LOG("PRESSED Dynamic Entity Deleter!");
            if (m_renderableObjects.size() > 0)
            {
                m_renderableObjects.pop_back();
//                g_tempTheta = g_theta;
//                g_popBackDone = true;
            }
        }

    }







    //m_renderableObjects[0]->Translate(glm::vec3(0.0f, 1.0f/100.0f, 0.0f));

    m_renderableObjects[0]->m_position.y += 1.0f/100.0f;
    //m_renderableObjects[0]->Rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));



    std::size_t lastEntityIndex = m_renderableObjects.size()-1;

    if(m_renderableObjects.size() >= 3)
    {
        OrbitAround(m_renderableObjects[3], m_renderableObjects[0]->m_position);
    }




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








