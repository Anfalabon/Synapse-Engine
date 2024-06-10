#pragma once


#include "../shader/Shader.hpp" //this is not to be used here but removing this causes error. Will fix it.
#include "../window/Window.hpp"
#include "../camera/Camera.hpp"

#include "../scene/Entities.hpp"
#include "../scene/Scene.hpp"

#include "../renderer/renderEntity.hpp"
#include "../debug/LOG.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <array>
#include <vector>
#include <future>
#include <mutex>
#include <memory>




#define PLATFORM

//#define __linux__
//#define __unix__

//class PLATFORM PhysicsEngine;
//class PLATFORM GraphicsEngine;



namespace Synapse
{


template<typename T>
static void Clean(T *ptr)
{
    if(ptr!=nullptr)
        delete ptr;
}


#ifdef __linux__

class [[nodiscard]] PLATFORM Engine
{
public:
    Engine() = default;
    ~Engine();

    static Engine &getInstance()
    {
        static Engine engine;
        return engine;
    }

    int8_t LoadGLFW();
    void   LoadWindow();
    int8_t LoadGLAD();
    void   SetViewPort();
    void   LoadEntitiesStatically();
    void   LoadScene();
    void   LoadCamera();
    void   LoadRenderer();


    void Update();


    [[nodiscard]] int8_t Init();
    void Run();

private:

    Window *m_window;
    Camera *m_camera;
    std::vector<RenderableObject*> m_entities;  //this should be Game engine objects but for now let's keep it as entities
    Scene *m_scene;
    EntityRenderer *m_renderer;
    //Renderer *m_renderer;
};




#elif defined(__WIN32__)
    DEBUG::__LOG__MANAGER__::LOG("WIN32 system not defined yet!");
#elif defined(__MAC__)
    DEBUG::__LOG__MANAGER__::LOG("MAC system not defined yet!");
#elif defined(__FreeBSD__)
    DEBUG::__LOG__MANAGER__::LOG("BSD system not defined yet!");
#elif defined(__ANDROID__)
    DEBUG::__LOG__MANAGER__::LOG("Android system not defined yet!");

#endif

}



