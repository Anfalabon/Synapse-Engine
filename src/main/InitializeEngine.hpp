#ifndef INITIALIZEENGINE_HPP
#define INITIALIZEENGINE_HPP

//#include <shader/Shader.hpp>

#include "../shader/Shader.hpp"
#include "../window/Window.hpp"
#include "../camera/Camera.hpp"
#include "../entity/Entities.hpp"
#include "../entity/CoordinateTransformation.hpp"
#include "../entity/vertexObjects.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <thread>


#define PLATFORM


//class PLATFORM PhysicsEngine;
//class PLATFORM GraphicsEngine;


class PLATFORM Engine
{
public:

    Engine() = default;
    ~Engine()
    {
//        delete camera;
//        delete cubesAndGround;
    }

    [[nodiscard]] virtual int8_t Run();

//private:
//    Window window = Window(1920.0f, 1080.0f, "Simulation Engine");
//    Camera *camera = new Camera();
//    std::vector<Entity*> entities;
//    Entity *cubesAndGround = new Entity();

};



class PLATFORM PhysicsEngine : Engine
{
public:
    PhysicsEngine() = default;

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

    [[nodiscard]] int8_t Run() override;


private:
    glm::vec3 m_entityPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_entityVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

};

class PLATFORM GraphicsEngine : Engine
{
    [[nodiscard]] int8_t Run() override;
};

#endif //INITIALIZEENGINE_HPP
