#pragma once

#include "Entities.hpp"
#include "ModelLoader.hpp"
#include "../physics/PhysicsEngine.hpp"
#include "../camera/Camera.hpp"

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
    void CreateRenderableObject(Synapse::Camera const *camera);
    void LoadRenderableObjectDynamically(GLFWwindow *window, Synapse::Camera const *camera);
    void RemoveRenderableObjectDynamically(GLFWwindow *window);
    void RenderableObjectKeyboardMovement(GLFWwindow *window, std::size_t index);
    void Update(GLFWwindow *window, Synapse::Camera const *camera, float deltaTime);
    void Clear();


    //void LoadRenderableObjectDynamically(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch);
    //void CreateRenderableObject(const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch);
    //void Update(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch, float deltaTime);

    //const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos, float yaw, float pitch



    [[nodiscard]] inline RenderableObject* GetRenderableObject(std::size_t index)
    {
        return (index<0) ? nullptr : m_renderableObjects[index];
    }

    [[nodiscard]] inline std::vector<Synapse::RenderableObject*> GetRenderableObjects(){return m_renderableObjects;}

    [[nodiscard]] inline std::size_t GetTotalSceneObjects(){return m_renderableObjects.size();};

private:

    inline void AddRenderableObject(const std::string &modelName)
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
    Synapse::Physics *m_physics;

    //temp member data's
    bool m_dynamicRenderableObjectLoaderRunning = false;
    bool m_dynamicRenderableObjectDeleterRunning = false;
    bool m_rotatorKeyPressed = false;
    float m_theta = 0.0f;   //this will be inside the 'Physics' class



};


}

