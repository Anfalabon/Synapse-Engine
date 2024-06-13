#pragma once


#include <glad/glad.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>


namespace Synapse
{


//inline glm::mat4 m_model = glm::mat4(1.0f);
//
//inline void SetModelMatrix(const glm::mat4 &model)
//{
//    m_model = model;
//}
//inline void SetModelMatrixLocation(GLuint shaderProgramID)
//{
//    GLuint modelLocation = glGetUniformLocation(shaderProgramID, "model");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));
//}


struct TransformComponent
{
public:

    TransformComponent(const glm::mat4 &model = glm::mat4(1.0f))
        : m_model(model){}
    ~TransformComponent() = default;

    void Translate(glm::vec3 translationVec)
    {
        m_model = glm::translate(m_model, translationVec);
    }

    void Rotate(float angleToRotateDegrees, glm::vec3 rotationVec)
    {
        m_model = glm::rotate(m_model, glm::radians(angleToRotateDegrees), rotationVec);
    }

    void Scale(glm::vec3 scaleVec)
    {
        m_model = glm::scale(m_model, scaleVec);
    }

private:
    glm::mat4 m_model;
};



struct Transformation
{
    Transformation() = default;

    glm::mat4 m_model = glm::mat4(1.0f);
    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_perspective = glm::mat4(1.0);

    //get the location of model matrix uniform in vertex shader
    inline void ModelLocation(GLuint shaderProgramID)
    {
        GLuint modelLocation = glGetUniformLocation(shaderProgramID, "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));

        //glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(m_model)));
    }

    //view and perspective matrix and location finder is going to be in the Camera class
    inline void ViewLocation(GLuint shaderProgramID)
    {
        GLuint viewLocation = glGetUniformLocation(shaderProgramID, "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_view));
    }

    //get the location of perspective matrix uniform in vertex shader
    inline void PerspectiveLocation(GLuint shaderProgramID)
    {
        GLuint perspectiveLocation = glGetUniformLocation(shaderProgramID, "perspective");
        glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(m_perspective));
    }


    void Translate(glm::vec3 translationVec)
    {
        m_model = glm::translate(m_model, translationVec);
    }

    void Rotate(float angleToRotateDegrees, glm::vec3 rotationVec)
    {
        m_model = glm::rotate(m_model, glm::radians(angleToRotateDegrees), rotationVec);
    }

    void Scale(glm::vec3 scaleVec)
    {
        m_model = glm::scale(m_model, scaleVec);
    }



};


typedef struct Transformation Transformation;


}
