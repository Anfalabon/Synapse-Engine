#ifndef INITIALIZEENGINE_HPP
#define INITIALIZEENGINE_HPP



#include "../shader/Shader.hpp"
#include "../window/Window.hpp"
#include "../camera/Camera.hpp"
#include "../entity/Entities.hpp"
#include "../entity/CoordinateTransformation.hpp"
#include "../entity/vertexObjects.hpp"
#include "../render/renderEntity.hpp"

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

    bool isInitSuccess;
    Window *window;
    Camera *camera;
    std::vector<Entity*> entities;  //this should be Game engine objects but for now let's keep it as entities
    Renderer renderer;
    std::vector<std::future<void>> futures;
};


#if 0

class PLATFORM PhysicsEngine : Engine
{
public:
    PhysicsEngine() = default;
    ~PhysicsEngine() = default;

    void setPos(const glm::vec3 &entityPos){m_entityPos = entityPos;}
    void setVelocity(const glm::vec3 &entityVelocity){m_entityVelocity = entityVelocity;}

    inline void changeHeight(GLfloat height) { m_entityPos.y = height; }
    inline void increaseHeight(GLfloat deltaHeight) { m_entityPos.y += deltaHeight; }
    inline void decreaseHeight(GLfloat deltaHeight) { m_entityPos -= deltaHeight; }

    inline void changeVerticalVelocity(GLfloat velocity) { m_entityVelocity.y = velocity; }
    inline void increaseVerticalVelocity(GLfloat deltaVelocity) { m_entityVelocity.y += deltaVelocity; }
    inline void decreaseVerticalVelocity(GLfloat deltaVelocity) { m_entityVelocity.y -= deltaVelocity; }

//    enum class CONSTANTS
//    {
//        PI = 3.14159f,
//        GRAVITY = 0.1f,
//        DELTATIME = 0.27f
//    };

    [[nodiscard]] int8_t Init() override;
    [[nodiscard]] int8_t Run() override;


private:
    glm::vec3 m_entityPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_entityVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

};

class PLATFORM GraphicsEngine : Engine
{
    GraphicsEngine() = default;
    ~GraphicsEngine() = default;

    [[nodiscard]] int8_t Init() override;
    [[nodiscard]] int8_t Run() override;
};

#endif

#endif //INITIALIZEENGINE_HPP
