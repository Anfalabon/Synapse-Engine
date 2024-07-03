#include "VertexArray.hpp"


namespace Synapse
{

void VertexArray::Gen()
{
    glGenVertexArrays(1, &_VAO);
}

void VertexArray::Bind()
{
    glBindVertexArray(_VAO);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::EnableVertexAttribute(unsigned short vertexAttributeNo, unsigned short objectsInCurrentAttribute, unsigned short objectsInSingleVertex)
{
    glVertexAttribPointer(vertexAttributeNo, objectsInCurrentAttribute, GL_FLOAT, GL_FALSE, objectsInSingleVertex * sizeof(GLfloat), (void*)(3*vertexAttributeNo * sizeof(GLfloat)));
    glEnableVertexAttribArray(vertexAttributeNo);
}


void VertexArray::SetVertexLayout(unsigned short vertexAttributeNo, unsigned short objectsInCurrentAttribute, unsigned short objectsInSingleVertex)
{
    glVertexAttribPointer(vertexAttributeNo, objectsInCurrentAttribute, GL_FLOAT, GL_FALSE, objectsInSingleVertex * sizeof(GLfloat), (void*)(3*vertexAttributeNo * sizeof(GLfloat)));
    glEnableVertexAttribArray(vertexAttributeNo);
}

}