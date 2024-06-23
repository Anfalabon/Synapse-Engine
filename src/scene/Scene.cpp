#include "Scene.hpp"
#include "../debug/LOG.hpp"
#include "../window/Window.hpp"
#include "entitiesAttributesData.hpp"
#include "../utils/RunParallel.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


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
    this->LoadRenderableObjectsStatically();
}


void Scene::LoadRenderableObjectsStatically()
{
    namespace data = entitiesData;




//    m_renderableObjects.push_back(new RenderableObject("Light Source", data::cubeVerticiesData, data::cubeIndiciesData));




    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[0]->SetName("Light Source");
    m_renderableObjects[0]->SetVerticies(data::cubeData::cubeTotalVerticies, data::cubeData::cubeVerticiesData);
    m_renderableObjects[0]->SetIndicies(data::cubeData::cubeTotalIndicies, data::cubeData::cubeIndiciesData);

    std::cout << "IS running?" << '\n';



//    m_renderableObjects.push_back(new RenderableObject());
//    m_renderableObjects[1]->SetName("Ground");
//    m_renderableObjects[1]->SetVerticies(data::groundData::groundTotalVerticies, data::groundData::groundVerticiesData);
//    m_renderableObjects[1]->SetIndicies(data::groundData::groundTotalIndicies, data::groundData::groundIndiciesData);



    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[1]->SetName("3D Trapizium");
    m_renderableObjects[1]->SetVerticies(data::anotherCubeData::anotherCubeTotalVerticies, data::anotherCubeData::anotherCubeVerticiesData);
    m_renderableObjects[1]->SetIndicies(data::anotherCubeData::anotherCubeTotalIndicies, data::anotherCubeData::anotherCubeIndiciesData);



    constexpr std::size_t nullEntities = 0;

    //for now this is because of the benchmarking
    //add null entities
    for(std::size_t i=m_renderableObjects.size()-1; i<nullEntities; ++i) [[unlikely]]
    {
        m_renderableObjects.push_back(new RenderableObject());
        m_renderableObjects[i]->SetName("Null Entity");
        m_renderableObjects[i]->SetVerticies(0, nullptr);
        m_renderableObjects[i]->SetIndicies(0, nullptr);
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
    namespace data = entitiesData;

    //adding a single scene(which is here a cube) causes adding of other entities.
    //will need to fix this



    m_renderableObjects.push_back(new RenderableObject());

    std::size_t lastEntityIndex = m_renderableObjects.size()-1;

    m_renderableObjects[lastEntityIndex]->SetName("Light Source");
    m_renderableObjects[lastEntityIndex]->SetVerticies(data::cubeData::cubeTotalVerticies, data::cubeData::cubeVerticiesData);
    m_renderableObjects[lastEntityIndex]->SetIndicies(data::cubeData::cubeTotalIndicies, data::cubeData::cubeIndiciesData);

    m_renderableObjects[lastEntityIndex]->LoadVertexObjects();

    float zToShift = -1.0f;

    m_renderableObjects[lastEntityIndex]->m_model = glm::translate(m_renderableObjects[lastEntityIndex]->m_model,
                                                                   currentCameraTargetPos + glm::vec3(0.0f, 0.0f, zToShift));

    //the model matrix will be modified using 'SendMatrix4ToGPU()'
}


bool g_dynamicRenderableObjectLoaderRunning = false;
bool g_dynamicRenderableObjectDeleterRunning = false;


void Scene::Update(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos)
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
            }
        }

    }



    std::size_t lastEntityIndex = m_renderableObjects.size()-1;




    m_renderableObjects[0]->Translate(glm::vec3(0.0f, 1.0f/100.0f, 0.0f));
    m_renderableObjects[0]->Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    m_renderableObjects[1]->Translate(glm::vec3(0.0f, -1.0f/100.0f, 0.0f));



    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, 1.0f/10.0f, 0.0f));
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, -1.0f/10.0f, 0.0f));
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








