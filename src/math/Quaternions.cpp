#include "Quaternions.hpp"


namespace Synapse
{


void Quaternions::ApplyQuaternions(RenderableObject *renderableObject, float theta, const glm::vec3 &axisOfRotation)
{
    theta = glm::radians(theta);

    float w = glm::cos(theta/2);
    float x = axisOfRotation.x * glm::sin(theta/2);
    float y = axisOfRotation.y * glm::sin(theta/2);
    float z = axisOfRotation.z * glm::sin(theta/2);

    glm::vec4 qPosition = glm::vec4(0, renderableObject->m_position.x , renderableObject->m_position.y, renderableObject->m_position.z);
    glm::vec4 q = glm::vec4(w, x, y, z);
    glm::vec4 qDash = glm::vec4(w, -1.0f*x, -1.0f*y, -1.0f*z);

    glm::vec4 rotatedPoint = q * qPosition * qDash;

    renderableObject->m_position.x = rotatedPoint.x;
    renderableObject->m_position.y = rotatedPoint.y;
    renderableObject->m_position.z = rotatedPoint.z;
}


}