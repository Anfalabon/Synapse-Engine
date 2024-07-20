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
    __ALWAYS__INLINE__ void RemoveViewer(){}
    __ALWAYS__INLINE__ unsigned int GetCurrentCameraIndexID() const {return m_currentCameraIndex;}
    __ALWAYS__INLINE__ SceneCamera &GetCurrentSceneCamera(){return m_sceneCameras[m_currentCameraIndex];}

    void LoadSceneCameras(unsigned int totalCameras, GLFWwindow *window);
    void SelectSceneCamera(GLFWwindow *window);

    //m_cameras[m_currentCameraIndex]->Update(m_window->WindowAddress(), m_renderer->GetShader(0), m_deltaTime);  //m_scene->GetRenderableObjects(),
    __ALWAYS__INLINE__ void Update(GLFWwindow *window, Shader &shader, const float deltaTime)
    {
        this->SelectSceneCamera(window);    //m_sceneViewer->SelectSceneCamera(m_window->WindowAddress());  //this is will be inside 'Update()' function of m_sceneViewer
        m_sceneCameras[m_currentCameraIndex].Update(window, shader, deltaTime);
    }

private:

    //we need fast insertion, deletion and access of any camera that we want
    //std::unordered_map<SceneCamera, unsigned int> m_sceneCamerasMap;

    //will use std::unordererd_map rather than std::vector for scene cameras
    std::vector<SceneCamera>            m_sceneCameras;
    unsigned int                        m_currentCameraIndex;
    std::unordered_map<int8_t, int8_t>  m_cameraIndexMap;
};

}