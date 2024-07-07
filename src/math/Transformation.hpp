#pragma once

#include <glad/glad.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "../scene/Entities.hpp"


namespace Synapse
{


class TransformComponent
{
public:
    TransformComponent() = default;
    ~TransformComponent() = default;

    static void Translate(RenderableObject *renderableObjet, const glm::vec3 &translationVec);
    static void Rotate(RenderableObject *renderableObject, const float angleToRotateDegrees, const glm::vec3 &rotationVec);
    static void Scale(RenderableObject *renderableObject, const glm::vec3 &scaleVec);
    static void ApplyQuaternions(RenderableObject *renderableObject, float theta, const glm::vec3 &axisOfRotation);

private:
};


}