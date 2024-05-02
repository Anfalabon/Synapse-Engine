#ifndef VERTEXOBJECTS_H
#define VERTEXOBJECTS_H

#include <glad/glad.hpp>
//#include "../external/glad/include/glad/glad.hpp"


typedef struct Vertex
{
    GLfloat positions[3];
    GLfloat colors[3];
}Vertex;


struct VertexObjects
{
public:
    explicit VertexObjects(GLuint verticiesSizeBytes, const void *verticiesData,
                           GLuint indiciesSizeBytes, const void *indiciesData) noexcept;
    ~VertexObjects();

    GLuint &getVBO(){return _VBO;}
    GLuint &getVAO(){return _VAO;}
    GLuint &getEBO(){return _EBO;}

private:
    GLuint _VBO;
    GLuint _VAO;
    GLuint _EBO;

    bool _elementBufferexist;

};


typedef struct Vertex Vertex;
typedef struct VertexObjects VertexObjects;


#endif //VERTEXOBJECTS_H
