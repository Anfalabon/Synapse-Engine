#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>


namespace Synapse
{


class EulerAngle
{
public:

    EulerAngle() = default;
    ~EulerAngle() = default;

    static void Rotate(glm::vec3 &vec, float yaw, float pitch);

private:
    float m_yaw;
    float m_pitch;
    float m_roll;
};


} // Synapse

