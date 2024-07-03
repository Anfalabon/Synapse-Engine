#include "IndexBuffer.hpp"


namespace Synapse
{


void IndexBuffer::SetIndicies(GLuint totalIndicies, GLuint *indiciesData)
{
    _totalIndicies = totalIndicies;
    _indiciesData = std::move(indiciesData);
}

void IndexBuffer::Gen()
{
    glGenBuffers(1, &_EBO);
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*_totalIndicies, _indiciesData, GL_STATIC_DRAW);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



}