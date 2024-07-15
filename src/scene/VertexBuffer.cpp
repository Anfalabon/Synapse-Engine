#include "VertexBuffer.hpp"


namespace Synapse
{


void VertexBuffer::SetVerticies(GLuint totalVerticies, float *verticiesData)
{
    //_totalVerticies = totalVerticies;
    //_verticiesData = std::move(verticiesData);
}

void VertexBuffer::Gen()
{
    glGenBuffers(1, &_VBO);
}

void VertexBuffer::Bind()
{
    //_verticiesData = &_vVerticiesData[0];
    unsigned long TARGET_BUFFER = 0x8892;   //GL_ARRAY_BUFFER
    glBindBuffer(TARGET_BUFFER, _VBO);
    glBufferData(TARGET_BUFFER, sizeof(float) * _verticiesData.size(), &_verticiesData[0], GL_STATIC_DRAW);
    //glBufferData(TARGET_BUFFER, sizeof(float) * _totalVerticies, &_verticiesData[0], GL_STATIC_DRAW);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


}

