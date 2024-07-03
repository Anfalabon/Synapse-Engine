#include "Transformation.hpp"



namespace Synapse
{


void TransformComponent::Translate(RenderableObject *renderableObject, const glm::vec3 &translationVec)
{
    renderableObject->m_model = glm::translate(renderableObject->m_model, translationVec);
}


void TransformComponent::Rotate(RenderableObject *renderableObjet, const float angleToRotateDegrees, const glm::vec3 &rotationVec)
{
    renderableObjet->m_model = glm::rotate(renderableObjet->m_model, glm::radians(angleToRotateDegrees), rotationVec);
}


void TransformComponent::Scale(RenderableObject *renderableObjet, const glm::vec3 &scaleVec)
{
    renderableObjet->m_model = glm::scale(renderableObjet->m_model, scaleVec);
}


}