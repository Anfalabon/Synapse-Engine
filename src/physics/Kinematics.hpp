#pragma once

#include "physics/PhysicsEngine.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


namespace Synapse
{

class Kinematics : public Physics
{
public:
    Kinematics() = default;
    ~Kinematics() = default;

    inline void InitPosition(const glm::vec3 &pos) { m_pos = pos; }
    inline void InitVelocity(const glm::vec3 &velocity) { m_velocity = velocity; }

    inline void ChangeHeight(GLfloat height) { m_pos.y = height; }
    inline void IncreaseHeight(GLfloat deltaHeight) { m_pos.y += deltaHeight; }
    inline void DecreaseHeight(GLfloat deltaHeight) { m_pos -= deltaHeight; }
    inline void ChangeVerticalVelocity(GLfloat velocity) { m_velocity.y = velocity; }
    inline void IncreaseVerticalVelocity(GLfloat deltaVelocity) { m_velocity.y += deltaVelocity; }
    inline void DecreaseVerticalVelocity(GLfloat deltaVelocity) { m_velocity.y -= deltaVelocity; }


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


    void FallDown() override;
    void Jump() override;
    void ApplyVerticalMotions() override;
private:
};

}

