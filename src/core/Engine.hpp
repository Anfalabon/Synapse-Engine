#pragma once

#include <glad/glad.hpp>

#include "../window/Window.hpp"
#include "../camera/Camera.hpp"
#include "../scene/Scene.hpp"
#include "../renderer/Renderer.hpp"

#include <vector>
#include <unordered_map>

namespace Synapse
{

class Engine
{
public:
    Engine() = default;
    ~Engine();

    int8_t LoadGLFW();
    void   LoadWindow();
    int8_t LoadGLAD();
    void   SetViewPort();
    void   LoadScene();
    void   LoadCamera();
    void   LoadRenderer();

    void   SelectCamera();

    void   Update();

    Window *GetWindow(){return m_window;}   //will remove this cause window will be inside 'Application' anyway

    [[nodiscard]] int8_t Init();
    void Run();
    void ShutDown();

private:

    Window          *m_window;
    Camera          *m_camera;
    Scene           *m_scene;
    SceneRenderer   *m_renderer;

    std::vector<Camera*> m_cameras;
    unsigned short       m_currentCameraIndex = 0;
    //std::unordered_map<std::size_t, Camera*> m_cameras;


    //Renderer      *m_renderer;

};


}



