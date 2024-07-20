#pragma once

#include "scene/Entities.hpp"
#include "scene/ModelLoader.hpp"
#include "physics/PhysicsEngine.hpp"
//#include "camera/Camera.hpp"
#include "scene/editor/SceneCamera.hpp"
#include "core/Macros.hpp"

#include <GLFW/glfw3.h>

//#define __ENTITY__COMPONENT_SYSTEM__

#if defined(__ENTITY__COMPONENT_SYSTEM__)
    #include <unordered_map>
#else
    #include <vector>
#endif



namespace Synapse
{

class Scene
{
public:
    Scene() = default;
    ~Scene();

    void Init();
    void LoadInitialRenderableObjects();
    void CreateRenderableObject(Synapse::SceneCamera *camera);   //make the camera parameter const
    void LoadRenderableObjectDynamically(GLFWwindow *window, Synapse::SceneCamera *camera);  //make the camera parameter const
    void RemoveRenderableObjectDynamically(GLFWwindow *window);
    void RenderableObjectKeyboardMovement(GLFWwindow *window, std::size_t index);
    void SelectRenderableObject(GLFWwindow *window, Synapse::SceneCamera *camera, const std::size_t renderableObjectIndex = 2);
    void Update(GLFWwindow *window, Synapse::SceneCamera *camera, float deltaTime);  //make the camera parameter const
    void Clear();


    //void LoadRenderableObjectDynamically(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch);
    //void CreateRenderableObject(const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch);
    //void Update(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch, float deltaTime);

    //const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch



    [[nodiscard]] __ALWAYS__INLINE__ RenderableObject* GetRenderableObject(std::size_t index)
    {
        return ((index<0) || (index>m_renderableObjects.size()-1)) ? nullptr : m_renderableObjects[index];
    }

    [[nodiscard]] __ALWAYS__INLINE__ std::vector<Synapse::RenderableObject*> &GetRenderableObjects(){return m_renderableObjects;}
    [[nodiscard]] __ALWAYS__INLINE__ std::size_t GetTotalSceneObjects(){return m_renderableObjects.size();};

private:

    //__ALWAYS__INLINE__ void AddRenderableObject(const std::string &modelName, const glm::vec3 &pos, const float rotationAngle, const float scale)
    __ALWAYS__INLINE__ void AddRenderableObject(const std::string &modelName)
    {
        m_renderableObjects.push_back(new RenderableObject(m_modelLoader->GetModel(modelName)));
    }

#if defined (__ENTITY__COMPONENT_SYSTEM__)
    class UUID; //later define if want to add 'ECS'
    std::unordered_map<UUID, RenderableObject*> m_renderableObjectsMap;
#else
    std::vector<Synapse::RenderableObject*> m_renderableObjects;
#endif

    Synapse::ModelLoader *m_modelLoader;

public:
    std::size_t m_firstCameraIndex               = 0;
private:

    //temp member data's
    bool m_dynamicRenderableObjectLoaderRunning  = false;
    bool m_dynamicRenderableObjectDeleterRunning = false;
    bool m_lookingAtRenderableObject               = false;


    bool m_wasClearMethodCalled = false;    //this is for preventing double free(once in 'Clear()' method and again in the destructor)



};


}

