#pragma once

#include <glad/glad.hpp>

#include "../window/Window.hpp"
#include "../camera/Camera.hpp"
#include "../scene/Scene.hpp"
#include "../renderer/Renderer.hpp"
#include "../physics/PhysicsEngine.hpp"
#include "../audio/Audio.hpp"
#include "../scripts/ScriptingEngine.hpp"

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
    void   SetViewPort();
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

private:

    Synapse::Window          *m_window;
    Synapse::Camera          *m_camera;
    Synapse::Scene           *m_scene;
    Synapse::SceneRenderer   *m_renderer;
    Synapse::Physics         *m_physics;
    Synapse::Audio           *m_audio;
    Synapse::ScriptingEngine *m_script;

    std::vector<Synapse::Camera*> m_cameras;
    unsigned short       m_currentCameraIndex;
public:
    bool                 m_engineRestart : 1;   //using bit fields for decreasing the size of a bool from 1 byte to 1 bit
private:
    //std::unordered_map<std::size_t, Camera*> m_cameras;
    //Renderer      *m_renderer;

};


}



