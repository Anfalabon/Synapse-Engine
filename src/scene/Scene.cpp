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

//    m_renderableObjects.push_back(new RenderableObject("light source cube",
//                                                        data::cubeData::cubeVerticiesData, data::cubeData::cubeTotalVerticies,
//                                                        data::cubeData::cubeIndiciesData, data::cubeData::cubeTotalIndicies,
//                                                        "../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
//                                                        "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf"));
//
//
//    m_renderableObjects.push_back(new RenderableObject("ground",
//                                                        data::groundData::groundVerticiesData, data::groundData::groundTotalVerticies,
//                                                        data::groundData::groundIndiciesData, data::groundData::groundTotalIndicies,
//                                                        "../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
//                                                        "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf"));
//
//
//    m_renderableObjects.push_back(new RenderableObject("anotherCube",
//                                                        data::anotherCubeData::anotherCubeVerticiesData, data::anotherCubeData::anotherCubeTotalVerticies,
//                                                        data::anotherCubeData::anotherCubeIndiciesData, data::anotherCubeData::anotherCubeTotalIndicies,
//                                                        "../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
//                                                        "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf"));










    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[0]->SetName("Light Source");
    m_renderableObjects[0]->SetVerticies(data::cubeData::cubeTotalVerticies, data::cubeData::cubeVerticiesData);
    m_renderableObjects[0]->SetIndicies(data::cubeData::cubeTotalIndicies, data::cubeData::cubeIndiciesData);
    m_renderableObjects[0]->SetShaderSources("../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
                                             "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf");






    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[1]->SetName("Ground");
    m_renderableObjects[1]->SetVerticies(data::groundData::groundTotalVerticies, data::groundData::groundVerticiesData);
    m_renderableObjects[1]->SetIndicies(data::groundData::groundTotalIndicies, data::groundData::groundIndiciesData);
    m_renderableObjects[1]->SetShaderSources("../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
                                             "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf");



    m_renderableObjects.push_back(new RenderableObject());
    m_renderableObjects[2]->SetName("3D Trapizium");
    m_renderableObjects[2]->SetVerticies(data::anotherCubeData::anotherCubeTotalVerticies, data::anotherCubeData::anotherCubeVerticiesData);
    m_renderableObjects[2]->SetIndicies(data::anotherCubeData::anotherCubeTotalIndicies, data::anotherCubeData::anotherCubeIndiciesData);
    m_renderableObjects[2]->SetShaderSources("../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
                                             "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf");


//    m_renderableObjects[0]->SetShaderSources("../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
//                                             "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf");


    //make any modification to the entities or scene after running useProgram() and before rendering otherwise it would be TOO bad!

//        entities[0]->getTransformation().translate(glm::vec3(0.0f, -0.01f, 0.0f));
//        entities[0]->getTransformation().modelLocation(entities[0]->getShader().ProgramID());


//    unsigned int entityIndex = 0;
//    m_renderableObjects[entityIndex]->Update();
//    m_renderableObjects[entityIndex]->m_model = glm::translate(m_renderableObjects[entityIndex]->m_model, glm::vec3(0.0f, -1.0f, 0.0f));

    constexpr std::size_t nullEntities = 0;

    //for now this is because of the benchmarking
    //add null entities
    for(std::size_t i=0; i<nullEntities; ++i) [[unlikely]]
    {
        m_renderableObjects.push_back(new RenderableObject("", nullptr, 0, nullptr, 0, "", ""));
    }


    for(RenderableObject *renderableObject: m_renderableObjects) [[likely]]
    {
        renderableObject->LoadVertexObjects();
        renderableObject->LoadShader();
    }

//    m_renderableObjects[0]->Update();
//    m_renderableObjects[0]->GetVA().Bind();
//    m_renderableObjects[0]->m_model = glm::translate(m_renderableObjects[0]->m_model, glm::vec3(0.0f, -1.0f, 0.0f));
//    m_renderableObjects[0]->GetShader().SendMatrix4ToGPU("model", m_renderableObjects[0]->m_model);

    //std::cin.get();
}


//have to fix and update this dynamic scene Loader which apparently doesn't work
void Scene::LoadRenderableObjectsDynamically()
{
    namespace data = entitiesData;

    //adding a single scene(which is here a cube) causes adding of other entities.
    //will need to fix this
//    m_renderableObjects.push_back(new RenderableObject("light source cube",
//                                              data::cubeData::cubeVerticiesData, data::cubeData::cubeTotalVerticies,
//                                              data::cubeData::cubeIndiciesData, data::cubeData::cubeTotalIndicies,
//                                              "../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
//                                              "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf"));



    m_renderableObjects.push_back(new RenderableObject());

    std::size_t lastEntityIndex = m_renderableObjects.size()-1;

    m_renderableObjects[lastEntityIndex]->SetName("Light Source");
    m_renderableObjects[lastEntityIndex]->SetVerticies(data::cubeData::cubeTotalVerticies, data::cubeData::cubeVerticiesData);
    m_renderableObjects[lastEntityIndex]->SetIndicies(data::cubeData::cubeTotalIndicies, data::cubeData::cubeIndiciesData);
    m_renderableObjects[lastEntityIndex]->SetShaderSources("../src/renderer/shader/GLSL/vertexShaderSource1.glslv",
                                                            "../src/renderer/shader/GLSL/fragmentShaderSource1.glslf");
    m_renderableObjects[lastEntityIndex]->LoadVertexObjects();
    m_renderableObjects[lastEntityIndex]->LoadShader();

    //m_camera->AddShaderProgramID(m_renderableObjects[lastEntityIndex]->GetShader().ProgramID());
    //m_renderableObjects[lastEntityIndex]->Translate(m_camera->GetTargetPos());

    m_renderableObjects[lastEntityIndex]->Translate(glm::vec3(0.0f, -10.0f, 0.0f));
}




void Scene::Update(GLFWwindow *window)
{
    if(m_renderableObjects.size() < 0)
    {
        return;
    }


    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS &&
       glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        DEBUG::__LOG__MANAGER__::LOG("PRESSED Dynamic Entity Loader!");
        this->LoadRenderableObjectsDynamically();
    }

    std::cout << "Scene updater is going to crash!" << '\n';
    std::cout << "Total renderable objects: " << m_renderableObjects.size() << '\n';    //this is causing crash
    //apply different transformation to the renderable objects if needed
    //but the objects are being treated like they are in one buffer
    //will NEED to fix it.

    //unsigned int entityIndex = 0;
    //m_renderableObjects[entityIndex]->Update();
    //m_renderableObjects[entityIndex]->m_model = glm::translate(m_renderableObjects[entityIndex]->m_model, glm::vec3(0.0f, -0.01f, 0.0f));
    //m_renderableObjects[entityIndex]->m_model = glm::rotate(m_renderableObjects[entityIndex]->m_model, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

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
        renderableObject->Update();
    }
#endif


    std::cout << "Completed updating current scene!" << '\n';


}




Scene::~Scene()
{
    for(std::size_t i=0; i<m_renderableObjects.size(); ++i)
    {
        m_renderableObjects[i]->GetShader().RemoveProgram();
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








