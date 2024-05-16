#ifndef INITIALIZEENGINE_HPP
#define INITIALIZEENGINE_HPP



#include "../shader/Shader.hpp"
#include "../window/Window.hpp"
#include "../camera/Camera.hpp"
#include "../entity/Entities.hpp"
#include "../entity/CoordinateTransformation.hpp"
#include "../entity/vertexObjects.hpp"
#include "../render/renderEntity.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vector>


#define PLATFORM


//class PLATFORM PhysicsEngine;
//class PLATFORM GraphicsEngine;

class PLATFORM Engine
{
public:
    Engine()
        :
        isInitSuccess(glfwInit()),    //initialize the glfw functions and other glfw features
        initialEntities(30003),
        window(1920.0f, 1080.0f, "Simulation Engine"),
        camera(new Camera()),
        renderer(Renderer(initialEntities)){}

    ~Engine()
    {
        delete camera;
    }

    [[nodiscard]] int8_t InitEntities(){}

    bool loadGLFW();
//    bool loadWindow();
    bool loadGLAD();
//    bool initViewPort(){glViewport();}
    bool loadCamera();
    bool loadEntities();
    bool loadRenderer();


    [[nodiscard]] int8_t Init();
    [[nodiscard]] int8_t Run();
private:

//#define GAME_MODE 0x1
//#define INSPECTION_MODE 0x2
//
//    uint8_t ENGINE_MODE = GAME_MODE;

    bool isInitSuccess;
    std::size_t initialEntities;
    Window window;
    Camera *camera;
    std::vector<Entity*> entities;
    Renderer renderer;
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
