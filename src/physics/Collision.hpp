#pragma once

#include "physics/PhysicsEngine.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Synapse
{

class Collision : public Physics
{
public:
    Collision() = default;
    ~Collision() = default;

    void SetCurrentObjectInfo(const glm::vec3 &objectMaxSize, const glm::vec3 &objectMinSize) override;
    bool WasCollided() override ;
private:
};


}
