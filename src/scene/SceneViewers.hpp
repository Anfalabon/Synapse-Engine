#pragma once

#include "scene/editor/SceneCamera.hpp"

#include <unordered_map>
#include <vector>



namespace Synapse
{

class SceneViewers
{
public:

    SceneViewers() = default;
    ~SceneViewers() = default;

    __ALWAYS__INLINE__ void AddViewer(const SceneCamera &camera){m_sceneCameras.push_back(camera);}
    __ALWAYS__INLINE__ void RemoteViewer(){}
    __ALWAYS__INLINE__ unsigned int GetCurrentCameraIndexID() const {return m_currentCameraIndex;}
    __ALWAYS__INLINE__ SceneCamera &GetCurrentSceneCamera()
    {
        return m_sceneCameras[m_currentCameraIndex];
    }

    void LoadSceneCameras(unsigned int totalCameras, GLFWwindow *window);
    void SelectSceneCamera(GLFWwindow *window);

private:

    //std::unordered_map<SceneCamera, unsigned int> m_sceneCamerasMap;

    //will use std::unordererd_map rather than std::vector for scene cameras
    std::vector<SceneCamera>            m_sceneCameras;
    unsigned int                        m_currentCameraIndex;
    std::unordered_map<int8_t, int8_t>  m_cameraIndexMap;
};

}