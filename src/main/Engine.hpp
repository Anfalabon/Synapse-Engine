#pragma once

#include <glad/glad.hpp>

#include "window/Window.hpp"
#include "scene/SceneViewers.hpp"
//#include "camera/Camera.hpp"
#include "scene/editor/SceneCamera.hpp"
#include "scene/Scene.hpp"
#include "renderer/Renderer.hpp"
#include "physics/PhysicsEngine.hpp"
#include "audio/Audio.hpp"
#include "scripting/ScriptingEngine.hpp"
#include "scene/animation/Animation.hpp"
#include "renderer/FrameBuffer.hpp"


#include <vector>
#include <unordered_map>

namespace Synapse
{


class Engine
{
public:
    Engine()
        :
          m_currentCameraIndex(0),
          m_engineRestart(false){}
    ~Engine();

public:

    [[nodiscard]] int8_t Init();

    void    Run();
    bool    Restart();
    void    ShutDown();

    Synapse::Window* GetWindow(){return m_window;}   //will remove this cause window will be inside 'Application' anyway

private:

    int8_t LoadGLFW();
    void   LoadWindow();
    int8_t LoadGLAD();
    void   LoadUI(){}
    void   LoadPhysicsEngine(){}
    void   LoadAudioEngine();
    void   LoadNetworkEngine(){}
    void   LoadAIEngine(){}
    void   LoadScene();
    void   LoadAnimator();
    void   LoadCameras();
    void   LoadSceneViewers();
    void   LoadRenderer();

    void   SelectCamera();
    void   CalculateDeltaTime();

private:

    Synapse::Window          *m_window;
    Synapse::SceneViewers    *m_sceneViewer;
    //Synapse::Camera          *m_camera;
    Synapse::Scene           *m_scene;
    Synapse::SceneRenderer   *m_renderer;
    Synapse::Physics         *m_physics;
    Synapse::Audio           *m_audio;
    Synapse::ScriptingEngine *m_script;
    Synapse::Animation       *m_animator;
    Synapse::FrameBuffer     *m_frameBuffer;

    //Synapse::Editor          *m_editor;

    std::vector<Synapse::SceneCamera*> m_cameras;
    unsigned short       m_currentCameraIndex;

public:
    bool                 m_engineRestart : 1;   //using bit fields for decreasing the size of a bool from 1 byte to 1 bit
    float                m_deltaTime = 0.0f;
    float                m_lastFrame = 0.0f;
private:
    //Synapse::Renderer      *m_renderer;

    std::unordered_map<int8_t, int8_t> m_cameraIndexMap;

};


}



