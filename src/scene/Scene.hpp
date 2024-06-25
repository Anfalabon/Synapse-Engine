#pragma once

#include "Entities.hpp"

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
    void LoadRenderableObjectsStatically();
    void LoadRenderableObjectsDynamically(const glm::vec3 &currentCameraTargetPos);
    void Update(GLFWwindow *window, const glm::vec3 &currentCameraTargetPos, const glm::vec3 &cameraPos);

    [[nodiscard]] inline RenderableObject* GetRenderableObject(std::size_t index)
    {
        return (index<0) ? nullptr : m_renderableObjects[index];
    }

    [[nodiscard]] inline std::vector<Synapse::RenderableObject*> GetRenderableObjects(){return m_renderableObjects;}

    [[nodiscard]] inline std::size_t GetTotalSceneObjects(){return m_renderableObjects.size();};

private:

#if defined (__ENTITY__COMPONENT_SYSTEM__)
    class UUID; //later define if want to add 'ECS'
    std::unordered_map<UUID, RenderableObject*> m_renderableObjectsMap;
#else
    std::vector<Synapse::RenderableObject*> m_renderableObjects;
#endif

};


}

