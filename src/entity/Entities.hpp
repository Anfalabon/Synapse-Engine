#ifndef ENTITIES_HPP
#define ENTITIES_HPP


#include <glad/glad.hpp>


//pretend like '../shader/Shader.hpp' is an library with '<>' lol
#include <../shader/Shader.hpp>
#include "CoordinateTransformation.hpp"
#include "vertexObjects.hpp"

#include <iostream>



class Entity
{
public:

    explicit Entity(Vertex *verticies, GLuint totalVerticies,
                    GLuint *indicies, GLuint totalIndicies,
                    const std::string &vertexShaderSourcePath,
                    const std::string &fragmentShaderSourcePath) noexcept;
    ~Entity();

    [[nodiscard]] inline Vertex *verticiesData(){return m_verticies;}
    [[nodiscard]] inline GLuint *indiciesData(){return m_indicies;}

    [[nodiscard]] inline GLuint verticiesSizeBytes(){return m_verticiesSizeBytes;}
    [[nodiscard]] inline GLuint indiciesSizeBytes(){return m_indiciesSizeBytes;}

    [[nodiscard]] inline GLuint totalverticies(){return m_totalVerticies;}
    [[nodiscard]] inline GLuint totalIndicies(){return m_totalIndicies;}



    [[nodiscard]] inline Shader& getShader(){return m_shader;}
    [[nodiscard]] inline CoordinateTransformation& getTransformation(){return m_coordinateTransform;}
    [[nodiscard]] inline VertexObjects& getVertexObjects(){return m_VO;}

    void loadShader();

//#ifdef __DEBUG__
    void printVerticiesData();
    void printIndiciesData();
//#endif

    //apply transformation to the Entity
    void translate(glm::vec3 translationVec);
    void rotate(float angleToRotateDegrees, glm::vec3 rotationVec);
    void scale();

    void render();
    void update();

private:

    const char* m_name = "Cube and cuboid object";

    Vertex *m_verticies = nullptr;
    GLuint *m_indicies = nullptr;

    GLuint m_totalVerticies;
    GLuint m_totalIndicies;

    GLuint m_verticiesSizeBytes;
    GLuint m_indiciesSizeBytes;

    //we can't use this if the Shader() constructor is explicit
    //Shader m_shader = Shader("../src/shader/GLSL/vertexShaderSource1.glslv", "../src/shader/GLSL/fragmentShaderSource1.glslf");
    Shader m_shader;
    struct CoordinateTransformation m_coordinateTransform;
    struct VertexObjects m_VO;
};





#endif // ENTITIES_HPP
