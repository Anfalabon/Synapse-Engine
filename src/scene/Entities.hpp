#pragma once



#include <glad/glad.hpp>


//pretend like '../shader/Shader.hpp' is an library with '<>' lol
#include "../shader/Shader.hpp"
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
    ~RenderableObject();

    [[nodiscard]] inline Vertex *verticiesData(){return m_verticies;}
    [[nodiscard]] inline GLuint *indiciesData(){return m_indicies;}

    [[nodiscard]] inline GLuint verticiesSizeBytes(){return m_verticiesSizeBytes;}
    [[nodiscard]] inline GLuint indiciesSizeBytes(){return m_indiciesSizeBytes;}

    [[nodiscard]] inline GLuint Totalverticies(){return m_totalVerticies;}
    [[nodiscard]] inline GLuint TotalIndicies(){return m_totalIndicies;}



    [[nodiscard]] inline Shader& GetShader(){return m_shader;}
    [[nodiscard]] inline Transformation& GetTransformation(){return m_Transform;}
    [[nodiscard]] inline VertexObjects& GetVertexObjects(){return m_VO;}

    void LoadShader();

//#ifdef __DEBUG__
    void PrintVerticiesData();
    void PrintIndiciesData();
//#endif

    //apply transformation to the Entity
    void Translate(glm::vec3 translationVec);
    void Rotate(float angleToRotateDegrees, glm::vec3 rotationVec);
    void Scale(glm::vec3 scaleVec);

    void Render();
    void Update();

private:

    const char* m_name;
    GLuint m_ID;

    Vertex *m_verticies = nullptr;
    GLuint *m_indicies = nullptr;

    GLuint m_totalVerticies;
    GLuint m_totalIndicies;

    GLuint m_verticiesSizeBytes;
    GLuint m_indiciesSizeBytes;

    //we can't use this if the Shader() constructor is explicit
    //Shader m_shader = Shader("../src/shader/GLSL/vertexShaderSource1.glslv", "../src/shader/GLSL/fragmentShaderSource1.glslf");
    Shader m_shader;
    struct Transformation m_Transform;
    struct VertexObjects m_VO;

public:
    //glm::mat4 m_model = glm::mat4(1.0f);
};



}
