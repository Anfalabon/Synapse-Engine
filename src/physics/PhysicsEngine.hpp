#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


namespace Synapse
{

struct Physics
{
public:

    struct PHYSICAL_CONSTANTS
    {
        static constexpr float PI = 3.14159f;
        static constexpr float GRAVITY = 0.1f;
        static constexpr float DELTATIME = 0.27f;
    };

    Physics() = default;

    ~Physics() = default;

    inline void CalculateDeltaTime()
    {
        float currentFrame = glfwGetTime();
        float currentDeltaTime = m_deltaTime;
        m_deltaTime = currentFrame - m_lastFrame;
        m_lastFrame = currentFrame;
    }

    //Kinematics
    inline void InitPosition(const glm::vec3 &pos) { m_pos = pos; }
    inline void InitVelocity(const glm::vec3 &velocity) { m_velocity = velocity; }

    inline void ChangeHeight(GLfloat height) { m_pos.y = height; }
    inline void IncreaseHeight(GLfloat deltaHeight) { m_pos.y += deltaHeight; }
    inline void DecreaseHeight(GLfloat deltaHeight) { m_pos -= deltaHeight; }
    inline void ChangeVerticalVelocity(GLfloat velocity) { m_velocity.y = velocity; }
    inline void IncreaseVerticalVelocity(GLfloat deltaVelocity) { m_velocity.y += deltaVelocity; }
    inline void DecreaseVerticalVelocity(GLfloat deltaVelocity) { m_velocity.y -= deltaVelocity; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline void InitPosX() {}
    inline void InitPosY() {}
    inline void InitPosZ() {}

    inline void InitVelocityX() {}
    inline void InitVelocityY() {}
    inline void InitVelocityZ() {}

    inline void IncreasePosX() {}
    inline void IncreasePosY() {}
    inline void IncreasePosZ() {}

    inline void IncreaseVelocityX() {}
    inline void IncreaseVelocityY() {}
    inline void IncreaseVelocityZ() {}


    inline void SetPosX() {}
    inline void SetPosY() {}
    inline void SetPosZ() {}

    inline void SetVelocityX() {}
    inline void SetVelocityY() {}
    inline void SetVelocityZ() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//protected:

    void SetCurrentObjectInfo(const glm::vec3 &objectMaxSize, const glm::vec3 &objectMinSize);
    inline void Reset() {}
    [[nodiscard]] bool WasCollided();
    void FallDown();
    void Jump();
    void ApplyVerticalMotions();
    void ApplyPhysics();


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

}


