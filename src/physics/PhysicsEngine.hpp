#pragma once

#include <stdio.h>
#include <glad/glad.hpp>
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

    void initPos(const glm::vec3 &pos){m_pos = pos;}
    void initVelocity(const glm::vec3 &velocity){m_velocity = velocity;}

    inline void changeHeight(GLfloat height) { m_pos.y = height; }
    inline void increaseHeight(GLfloat deltaHeight) { m_pos.y += deltaHeight; }
    inline void decreaseHeight(GLfloat deltaHeight) { m_pos -= deltaHeight; }

    inline void changeVerticalVelocity(GLfloat velocity) { m_velocity.y = velocity; }
    inline void increaseVerticalVelocity(GLfloat deltaVelocity) { m_velocity.y += deltaVelocity; }
    inline void decreaseVerticalVelocity(GLfloat deltaVelocity) { m_velocity.y -= deltaVelocity; }

    bool wasCollided();
    void fallDown();
    void jump();
    void applyVerticalMotions();

    void applyPhysics();




    [[nodiscard]] int8_t Init();
    [[nodiscard]] int8_t Run();


    //will name it 'm_pos' from 'm_entityPos' and same with 'm_entityVelocity'
    glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    bool m_jumped = false;
    bool m_collided = false;
    bool m_crouch = false;

    float m_initialHeight = 0.0f;
    float m_currentObjectHeight = 0.0f;

};


#endif