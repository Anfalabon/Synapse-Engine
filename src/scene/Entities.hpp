#pragma once

#include <glad/glad.hpp>
#include <glm/glm.hpp>

#include "../renderer/shader/Shader.hpp"
#include "Transformation.hpp"
#include "vertexObjects.hpp"

#include <iostream>



namespace Synapse
{


class RenderableObject
{
public:

    explicit RenderableObject(const char *name,
                    Vertex *verticies, GLuint totalVerticies,
                    GLuint *indicies, GLuint totalIndicies,
                    const std::string &vertexShaderSourcePath,
                    const std::string &fragmentShaderSourcePath) noexcept;


    RenderableObject() = default;
    ~RenderableObject();


    void SetName(const char* name);
    void SetID(){}
    void SetVerticies(GLuint totalVerticies, Vertex *verticies);
    void SetIndicies(GLuint totalIndicies, GLuint *indicies);
    void SetShaderSources(const std::string &vertexShaderSourcePath, const std::string &fragmentShaderSourcePath);

    void LoadVertexObjects();
    void LoadShader();

    [[nodiscard]] inline struct VertexArray&  GetVA(){return m_VA;}
    [[nodiscard]] inline struct VertexBuffer& GetVB(){return m_VB;}
    [[nodiscard]] inline struct IndexBuffer&  GetEB(){return m_EB;}

    [[nodiscard]] inline glm::mat4& GetModelMatrix(){return m_model;}

    [[nodiscard]] inline Shader& GetShader(){return m_shader;}
    [[nodiscard]] inline Transformation& GetTransformation(){return m_Transform;}


    //apply transformation to the Entity
    void Translate(glm::vec3 translationVec);
    void Rotate(float angleToRotateDegrees, glm::vec3 rotationVec);
    void Scale(glm::vec3 scaleVec);

    void Update();

private:

    const char* m_name;
    GLuint      m_ID;

    //we can't use this if the Shader() constructor is explicit
    //Shader m_shader = Shader("../src/shader/GLSL/vertexShaderSource1.glslv", "../src/shader/GLSL/fragmentShaderSource1.glslf");
public:
    glm::vec3             m_position = glm::vec3(0.0f, 0.0f, 0.0f);
private:
    Shader                m_shader;
    struct Transformation m_Transform;
    struct VertexArray    m_VA;
    struct VertexBuffer   m_VB;
    struct IndexBuffer    m_EB;

public:
    glm::mat4 m_model = glm::mat4(1.0f);
};



}
