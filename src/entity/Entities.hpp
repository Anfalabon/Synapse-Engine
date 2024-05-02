#ifndef ENTITIES_HPP
#define ENTITIES_HPP


#include <glad/glad.hpp>

#include "../shader/Shader.hpp"
#include "CoordinateTransformation.hpp"
#include "vertexObjects.hpp"

#include <iostream>



class Entity
{
public:

    explicit Entity(Vertex *verticiesArr, GLuint totalVerticies,
                    GLuint *indiciesArr, GLuint totalIndicies,
                    const std::string &vertexShaderSourcePath,
                    const std::string &fragmentShaderSourcePath) noexcept;
    ~Entity();

    [[nodiscard]] inline Vertex *verticiesData(){return m_verticies;}
    [[nodiscard]] inline GLuint *indiciesData(){return m_indicies;}

    [[nodiscard]] inline GLuint verticiesSizeBytes(){return m_verticiesSizeBytes;}
    [[nodiscard]] inline GLuint indiciesSizeBytes(){return m_indiciesSizeBytes;}

    [[nodiscard]] inline GLuint totalverticies(){return m_totalVerticies;}
    [[nodiscard]] inline GLuint totalIndicies(){return m_totalIndicies;}

    void setShader(const std::string &vertexShaderSourcePath,
                   const std::string &fragmentShaderSourcePath);

    void setVO();

    [[nodiscard]] inline Shader& getShader(){return m_shader;}
    [[nodiscard]] inline CoordinateTransformation& getTransformation(){return m_transform;}

    [[nodiscard]] inline VertexObjects& getVertexObjects(){return m_VO;}

    void printVerticiesData();
    void printIndiciesData();

    void render();
    void update();

private:

    const char* m_name = "Cube and cuboid object";

    //there are total of four entity verticies in one single verticies
    //we need to separate them for different kinds of operations and modularity


    Vertex *m_verticies = nullptr;
    GLuint *m_indicies = nullptr;

    GLuint m_totalVerticies;
    GLuint m_totalIndicies;

    GLuint m_verticiesSizeBytes;
    GLuint m_indiciesSizeBytes;

    //we can't use this if the Shader() constructor is explicit
    //Shader m_shader = Shader("../src/shader/GLSL/vertexShaderSource1.glslv", "../src/shader/GLSL/fragmentShaderSource1.glslf");
    Shader m_shader;
    struct CoordinateTransformation m_transform;
    struct VertexObjects m_VO;
};





#endif // ENTITIES_HPP
