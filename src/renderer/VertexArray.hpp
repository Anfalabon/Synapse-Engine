#pragma once

#include <glad/glad.hpp>

#include "scene/VertexBuffer.hpp"
#include "scene/IndexBuffer.hpp"

//#include <src/scene/VertexBuffer.hpp>
//#include <src/scene/IndexBuffer.hpp>


#include <iostream>
#include <array>
#include <vector>



namespace Synapse
{


class VertexArray
{
public:
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





