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

    RenderableObject() = default;
    ~RenderableObject();

    explicit RenderableObject(const char *name,
                    Vertex *verticies, GLuint totalVerticies,
                    GLuint *indicies, GLuint totalIndicies) noexcept;


    explicit RenderableObject(const char *name, Vertex *verticies, unsigned int *indicies) noexcept{}




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


    void Update();

private:

    const char* m_name;
    GLuint      m_ID;

    //we can't use this if the Shader() constructor is explicit
    //Shader m_shader = Shader("../src/shader/GLSL/vertexShader1.vert", "../src/shader/GLSL/fragmentShader1.frag");
private:
    struct VertexArray    m_VA;
    struct VertexBuffer   m_VB;
    struct IndexBuffer    m_EB;

public:
    glm::vec3 m_position = glm::vec3(0.0f, 1.0f/100.0f, 0.0f);
    glm::mat4 m_model = glm::mat4(1.0f);
};



}
