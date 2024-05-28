#pragma once


#include "../shader/Shader.hpp"
#include "../window/Window.hpp"
#include "../camera/Camera.hpp"
#include "../entity/Entities.hpp"
#include "../entity/CoordinateTransformation.hpp"
#include "../entity/vertexObjects.hpp"
#include "../renderer/renderEntity.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <future>
#include <mutex>



#define PLATFORM


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

class [[nodiscard]] PLATFORM Engine
{
public:
    Engine() = default;

    ~Engine()
    {
        Clean(m_camera);
        Clean(m_window);
        Clean(m_renderer);
    }

    int8_t LoadGLFW();
    void   LoadWindow();
    int8_t LoadGLAD();
    void   SetViewPort();
    void   LoadEntities();
    void   LoadCamera();
    void   LoadRenderer();

    [[nodiscard]] int8_t Init();
    [[nodiscard]] int8_t Init(const unsigned int &);
    [[nodiscard]] int8_t Run();

private:

    Window *m_window;
    Camera *m_camera;
    std::vector<Entity *> m_entities;  //this should be Game engine objects but for now let's keep it as entities
    EntityRenderer *m_renderer;
    //Renderer *m_renderer;
};

}
