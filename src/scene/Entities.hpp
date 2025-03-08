#pragma once

#include <glad/glad.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "scene/Mesh.hpp"
#include "scene/VertexBuffer.hpp"
#include "scene/IndexBuffer.hpp"
#include "renderer/VertexArray.hpp"
#include "renderer/Texture.hpp"

#include <iostream>
#include <vector>


//we can't use this if the Shader() constructor is explicit
//Shader m_shader = Shader("../src/shader/GLSL/vertexShader1.vert", "../src/shader/GLSL/fragmentShader1.frag");



namespace Synapse
{


//will name it GameObject
class RenderableObject
{
public:

    //explicit RenderableObject(const std::pair<std::string, Mesh> &model, const char *textureImageFilePath);
    //explicit RenderableObject(const std::vector<Mesh> &meshes);
    RenderableObject() = default;

    explicit RenderableObject(const std::pair<std::string, std::vector<Synapse::Mesh>> &model);
    explicit RenderableObject(const RenderableObject &) = default;
    RenderableObject &operator=(const RenderableObject &) = default;

    ~RenderableObject();

    void LoadMeshes();

    [[nodiscard]] __ALWAYS__INLINE__ std::string GetName(){return m_name;}

    [[nodiscard]] __ALWAYS__INLINE__ unsigned int GetTotalIndiciesOfMesh(std::size_t index)
    {
        //return (index < 0) ? 0 : m_meshes[index]._EB.GetTotalIndicies();
        return (index < 0) ? 0 : m_meshes[index].GetTotalIndicies();
    }

    [[nodiscard]] __ALWAYS__INLINE__ std::size_t GetTotalMeshes() const {return m_meshes.size();}

    [[nodiscard]] __ALWAYS__INLINE__ Mesh &GetMesh(std::size_t index)
    {
        //return (index < 0) ? Mesh() : m_meshes[index];
        return m_meshes[index];
    }

    [[nodiscard]] __ALWAYS__INLINE__ glm::mat4& GetModelMatrix(){return m_model;}

    __ALWAYS__INLINE__ void SetPosition(const glm::vec3 &position){m_position = position;}

    [[nodiscard]] __ALWAYS__INLINE__ glm::vec3 GetPosition() const
    {
        //glm::mat4 inverseModelMatrix = glm::inverse(m_model);
        //glm::vec3 position = std::move(inverseModelMatrix[3]);
        //position.x *= -1.0f;
        //position.y *= -1.0f;
        //position.z *= -1.0f;
        return m_position;
    }

    void Update();

private:

    std::string     m_name;
    unsigned int    m_ID;

    //this is useful for collision deltection and stuffs like that
    glm::vec3       m_minSize;
    glm::vec3       m_maxSize;

    std::vector<Synapse::Mesh> m_meshes;

public:

    glm::vec3 m_position        = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_rotationAngles  = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_rotation        = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 m_scaling         = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 m_velocity        = glm::vec3(1.0f, 0.0f, 1.0f); //the initial velocities will be
    glm::vec3 m_initialVelocity = m_velocity;
    glm::mat4 m_model           = glm::mat4(1.0f);

    float m_rotationAngle       = 0.0f;



};



}
