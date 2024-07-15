#pragma once


#include "scene/Entities.hpp"

namespace Synapse
{

struct Quaternions
{
public:
    Quaternions() = default;
    ~Quaternions() = default;

    static void ApplyQuaternions(RenderableObject *renderableObject, float theta, const glm::vec3 &axisOfRotation);

private:
    float m_w;
    float m_x;
    float m_y;
    float m_z;
};


} // Synapse

