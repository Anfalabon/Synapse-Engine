#pragma once

#include <glad/glad.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "Mesh.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "../renderer/Texture.hpp"

#include <iostream>
#include <vector>


namespace Synapse
{


//will name it GameObject
class RenderableObject
{
public:

    RenderableObject() = delete;
    explicit RenderableObject(const std::pair<std::string, Mesh> &model, const char *textureImageFilePath);
    //explicit RenderableObject(Model modelData);
    //explicit RenderableObject(const std::vector<Mesh> &meshes);
    ~RenderableObject();

    void LoadMeshes();
    void LoadVertexObjects(unsigned short objectsInSingleVertex = 0, bool addTexture = false);
    void LoadTexture();

    [[nodiscard]] inline VertexArray&  GetVA(){return m_VA;}
    [[nodiscard]] inline VertexBuffer& GetVB(){return m_VB;}
    [[nodiscard]] inline IndexBuffer&  GetEB(){return m_EB;}

    [[nodiscard]] inline unsigned int GetTotalIndicies(){return m_EB.GetTotalIndicies();}
    [[nodiscard]] inline unsigned int GetTotalMeshes(){return m_meshes.size();}
    [[nodiscard]] inline unsigned int GetTextureID(){return m_texture.GetTextureID();}

    [[nodiscard]] inline unsigned int GetTotalIndiciesOfMesh(std::size_t index)
    {
        return (index < 0) ? 0 : m_meshes[index]._EB.GetTotalIndicies();
    }

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

    std::vector<Mesh> m_meshes;

    VertexArray    m_VA;
    VertexBuffer   m_VB;
    IndexBuffer    m_EB;
    Texture        m_texture;

public:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_velocity = glm::vec3(1.0f, 0.0f, 1.0f); //the initial velocities will be
    glm::vec3 m_initialVelocity = m_velocity;
    glm::mat4 m_model = glm::mat4(1.0f);

};



}
