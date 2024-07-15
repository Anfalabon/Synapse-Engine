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

    void FallDown();
    void Jump();
    void ApplyVerticalMotions();

private:
};

}

