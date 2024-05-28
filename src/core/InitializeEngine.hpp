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
        Clean(camera);
        Clean(window);
        Clean(renderer);
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

    Window *window;
    Camera *camera;
    std::vector<Entity *> entities;  //this should be Game engine objects but for now let's keep it as entities
    EntityRenderer *renderer;
    //Renderer *renderer;
};

}


#if 0

class PLATFORM GraphicsEngine : Engine
{
    GraphicsEngine() = default;
    ~GraphicsEngine() = default;

    [[nodiscard]] int8_t Init() override;
    [[nodiscard]] int8_t Run() override;
};

#endif

