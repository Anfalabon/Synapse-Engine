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
    //explicit RenderableObject(const std::pair<std::string, Mesh> &model, const char *textureImageFilePath);
    explicit RenderableObject(const std::pair<std::string, Mesh> &model);
    //explicit RenderableObject(const std::vector<Mesh> &meshes);
    ~RenderableObject();

    void LoadMeshes();


    [[nodiscard]] inline unsigned int GetTotalIndiciesOfMesh(std::size_t index)
    {
        return (index < 0) ? 0 : m_meshes[index]._EB.GetTotalIndicies();
    }

    [[nodiscard]] inline Mesh& GetMesh(std::size_t index)
    {
        //return (index < 0) ? Mesh() : m_meshes[index];
        return m_meshes[index];
    }

    [[nodiscard]] inline glm::mat4& GetModelMatrix(){return m_model;}

    void SetPosition(const glm::vec3 &position){m_position = position;}
    [[nodiscard]] inline auto GetPosition()->glm::vec3
    {
        glm::mat4 inverseModelMatrix = glm::inverse(m_model);
        glm::vec3 position = std::move(inverseModelMatrix[3]);
        position.x *= -1.0f;
        position.y *= -1.0f;
        position.z *= -1.0f;
        return position;
    }


    void Translate(const glm::vec3 &translationVec);
    void Rotate(float angleToRotateDegrees, bool x, bool y, bool z);
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

public:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_velocity = glm::vec3(1.0f, 0.0f, 1.0f); //the initial velocities will be
    glm::vec3 m_initialVelocity = m_velocity;
    glm::mat4 m_model = glm::mat4(1.0f);

};



}
