#pragma once


#include <glad/glad.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>


namespace Synapse
{



struct TransformComponent
{
    TransformComponent() = default;
    ~TransformComponent() = default;

//    void Translate(glm::vec3 &model, glm::vec3 translationVec)
//    {
//        model = glm::translate(model, translationVec);
//    }
//
//    void Rotate(glm::mat4 &model, float angleToRotateDegrees, glm::vec3 rotationVec)
//    {
//        model = glm::rotate(model, glm::radians(angleToRotateDegrees), rotationVec);
//    }
//
//    void Scale(glm::mat4 &model, glm::vec3 scaleVec)
//    {
//        model = glm::scale(model, scaleVec);
//    }

};



}
