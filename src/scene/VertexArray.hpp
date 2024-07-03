#pragma once

#include <glad/glad.hpp>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <iostream>
#include <array>
#include <vector>



namespace Synapse
{


struct VertexArray
{
    VertexArray() = default;
    ~VertexArray()
    {
        glDeleteVertexArrays(1, &_VAO);
    }

    void Gen();
    void Bind();
    void Unbind();
    void SetVertexLayout(unsigned short vertexAttributeNo, unsigned short objectsInCurrentAttribute, unsigned short objectsInSingleVertex);
    void EnableVertexAttribute(unsigned short vertexAttributeNo, unsigned short objectsInCurrentAttribute, unsigned short objectsInSingleVertex);
    GLuint &GetVAO(){return _VAO;}

//private:
    GLuint _VAO;
    //unsigned short objectsInSingleVertex;
};


}





