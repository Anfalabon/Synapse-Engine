#pragma once

//#include "../../Synapse.hpp"


#include <glad/glad.hpp>

#include "window/Window.hpp"
#include "camera/Camera.hpp"
#include "scene/Scene.hpp"
#include "renderer/Renderer.hpp"
#include "physics/PhysicsEngine.hpp"
#include "audio/Audio.hpp"
#include "scripting/ScriptingEngine.hpp"
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

    int8_t LoadGLFW();
    void   LoadWindow();
    int8_t LoadGLAD();
    void   LoadUI(){}
    void   LoadPhysicsEngine(){}
    void   LoadAudioEngine();
    void   LoadNetworkEngine(){}
    void   LoadAIEngine(){}
    void   LoadScene();
    void   LoadCameras();
    void   LoadRenderer();


    bool   Restart();
    void   SelectCamera();

    Synapse::Window* GetWindow(){return m_window;}   //will remove this cause window will be inside 'Application' anyway

    [[nodiscard]] int8_t Init();

#define __RUN__ENGINE__
#ifdef __UPDATE__ENGINE__
    void                 Update();
#elif defined(__RUN__ENGINE__)
    void                 Run();
#endif

    void                 ShutDown();


    void CalculateDeltaTime();

private:

    Synapse::Window          *m_window;
    Synapse::Camera          *m_camera;
    Synapse::Scene           *m_scene;
    Synapse::SceneRenderer   *m_renderer;
    Synapse::Physics         *m_physics;
    Synapse::Audio           *m_audio;
    Synapse::ScriptingEngine *m_script;
    Synapse::FrameBuffer     *m_frameBuffer;

    //Synapse::Editor          *m_editor;

    std::vector<Synapse::Camera*> m_cameras;
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



