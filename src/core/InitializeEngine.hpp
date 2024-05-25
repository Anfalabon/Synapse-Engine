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


template<typename T>
static void clean(T *ptr)
{
    if(ptr!=nullptr)
        delete ptr;
}



#define PLATFORM


//class PLATFORM PhysicsEngine;
//class PLATFORM GraphicsEngine;



class [[nodiscard]] PLATFORM Engine
{
public:
    Engine() = default;

    ~Engine()
    {
        clean(camera);
        clean(window);
        clean(renderer);
    }
    
    int8_t loadGLFW();
    void   loadWindow();
    int8_t loadGLAD();
    void   setViewPort();
    void   loadEntities();
    void   loadCamera();
    void   loadRenderer();


    [[nodiscard]] int8_t Init();
    [[nodiscard]] int8_t Init(const unsigned int&);
    [[nodiscard]] int8_t Run();
private:

    Window *window;
    Camera *camera;
    std::vector<Entity*> entities;  //this should be Game engine objects but for now let's keep it as entities
    EntityRenderer *renderer;
    //Renderer *renderer;
};


#if 0

class PLATFORM GraphicsEngine : Engine
{
    GraphicsEngine() = default;
    ~GraphicsEngine() = default;

    [[nodiscard]] int8_t Init() override;
    [[nodiscard]] int8_t Run() override;
};

#endif

