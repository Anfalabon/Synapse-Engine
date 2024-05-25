#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>



#ifndef PLATFORM
#define PLATFORM



struct PLATFORM PhysicsEngine
{
public:

    struct PHYSICAL_CONSTANTS
    {
        static constexpr float PI = 3.14159f;
        static constexpr float GRAVITY = 0.1f;
        static constexpr float DELTATIME = 0.27f;
    };

    PhysicsEngine() = default;
    ~PhysicsEngine() = default;

    inline void calculateDeltaTime()
    {
        float currentFrame = glfwGetTime();
        float currentDeltaTime = m_deltaTime;
        m_deltaTime = currentFrame - m_lastFrame;
        m_lastFrame = currentFrame;
    }



    inline void initPosition(const glm::vec3 &pos){m_pos = pos;}
    inline void initVelocity(const glm::vec3 &velocity){m_velocity = velocity;}

    inline void changeHeight(GLfloat height){m_pos.y = height;}
    inline void increaseHeight(GLfloat deltaHeight){m_pos.y += deltaHeight;}
    inline void decreaseHeight(GLfloat deltaHeight){m_pos -= deltaHeight;}

    inline void changeVerticalVelocity(GLfloat velocity){m_velocity.y = velocity;}
    inline void increaseVerticalVelocity(GLfloat deltaVelocity){m_velocity.y += deltaVelocity;}
    inline void decreaseVerticalVelocity(GLfloat deltaVelocity){m_velocity.y -= deltaVelocity;}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline void initPosX(){}
    inline void initPosY(){}
    inline void initPosZ(){}

    inline void initVelocityX(){}
    inline void initVelocityY(){}
    inline void initVelocityZ(){}


    inline void increasePosX(){}
    inline void increasePosY(){}
    inline void increasePosZ(){}

    inline void increaseVelocityX(){}
    inline void increaseVelocityY(){}
    inline void increaseVelocityZ(){}


    inline void setPosX(){}
    inline void setPosY(){}
    inline void setPosZ(){}

    inline void setVelocityX(){}
    inline void setVelocityY(){}
    inline void setVelocityZ(){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    void setCurrentObjectInfo(const glm::vec3 &objectMaxSize, const glm::vec3 &objectMinSize);

    inline void reset(){}

    [[nodiscard]] bool wasCollided();
    void fallDown();
    void jump();
    void applyVerticalMotions();

    void applyPhysics();




    [[nodiscard]] int8_t Init();
    [[nodiscard]] int8_t Run();


    //will name it 'm_pos' from 'm_entityPos' and same with 'm_entityVelocity'
    glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 m_posWhileCollision;
    glm::vec3 m_objectMaxSize;
    glm::vec3 m_objectMinSize;

    bool m_jumped = false;
    bool m_collided = false;
    bool m_crouch = false;
    bool m_isAtTheRoof = false;
    bool m_keepPhysicsRunning = false;

    float m_initialHeight = 0.0f;
    float m_currentObjectHeight = 0.0f;

    float m_timeElapsed = 0.0f;
    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;

};


#endif