#ifndef VERTEXOBJECTS_H
#define VERTEXOBJECTS_H

#include <glad/glad.hpp>
//#include "../external/glad/include/glad/glad.hpp"

#include <iostream>


typedef struct Vertex
{
    GLfloat positions[3];
    GLfloat colors[3];

    inline friend std::ostream &operator<<(std::ostream &os, const struct Vertex &vertex);
}Vertex;



std::ostream &operator<<(std::ostream &os, const struct Vertex &vertex)
{
    os << vertex;
    return os;
}


struct VertexObjects
{
public:
    explicit VertexObjects(GLuint verticiesSizeBytes, const void *verticiesData,
                           GLuint indiciesSizeBytes, const void *indiciesData) noexcept;
    ~VertexObjects();

    [[nodiscard]] inline GLuint &getVAO(){return _VAO;}
    [[nodiscard]] inline GLuint &getEBO(){return _EBO;}
    [[nodiscard]] inline GLuint &getVBO(){return _VBO;}

private:
    GLuint _VBO;
    GLuint _VAO;
    GLuint _EBO;

    bool _elementBufferexist;

};


typedef struct Vertex Vertex;
typedef struct VertexObjects VertexObjects;


#endif //VERTEXOBJECTS_H
