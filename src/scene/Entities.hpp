#pragma once

#include <glad/glad.hpp>
#include <glm/glm.hpp>

#include "EntityLoader.hpp"
#include "Transformation.hpp"
#include "vertexObjects.hpp"

#include <iostream>
#include <unordered_map>



namespace Synapse
{

//will name it GameObject
class RenderableObject
{
public:

    RenderableObject() = default;
    explicit RenderableObject(Model<float> modelData);
    ~RenderableObject();


    void SetName(const char* name);
    void SetID(){}
    void SetVerticies(GLuint totalVerticies, float *verticies);
    void SetIndicies(GLuint totalIndicies, GLuint *indicies);
    void SetShaderSources(const std::string &vertexShaderSourcePath, const std::string &fragmentShaderSourcePath);

    void LoadVertexObjects(unsigned short objectsInSingleVertex = 0, bool addTexture = false);
    void LoadTexture();
    void LoadShader();

    [[nodiscard]] inline struct VertexArray&  GetVA(){return m_VA;}
    [[nodiscard]] inline struct VertexBuffer<float>& GetVB(){return m_VB;}
    [[nodiscard]] inline struct IndexBuffer&  GetEB(){return m_EB;}

    [[nodiscard]] inline unsigned int GetTotalIndicies(){return m_EB.GetTotalIndicies();}

    [[nodiscard]] inline glm::mat4& GetModelMatrix(){return m_model;}

    void SetPosition(const glm::vec3 &position){m_position = position;}
    [[nodiscard]] inline auto GetPosition()->glm::vec3{return m_position;}


    void Translate(const glm::vec3 &translationVec);
    void Rotate(float angleToRotateDegrees, const glm::vec3 &rotationVec);
    void Scale(const glm::vec3 &scaleVec);

    void Update();

private:

    const char* m_name;
    GLuint      m_ID;

    //we can't use this if the Shader() constructor is explicit
    //Shader m_shader = Shader("../src/shader/GLSL/vertexShader1.vert", "../src/shader/GLSL/fragmentShader1.frag");
private:
    struct VertexArray    m_VA;
    struct VertexBuffer<float>   m_VB;
    struct IndexBuffer    m_EB;

public:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_velocity = glm::vec3(1.0f, 0.0f, 1.0f); //the initial velocities will be
    glm::vec3 m_initialVelocity = m_velocity;
    glm::mat4 m_model = glm::mat4(1.0f);

    unsigned int textureID;
};



}
