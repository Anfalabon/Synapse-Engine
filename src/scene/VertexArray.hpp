#pragma once

#include <glad/glad.hpp>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <iostream>
#include <array>
#include <vector>



struct VertexArray
{
    VertexArray() = default;
    ~VertexArray()
    {
        glDeleteVertexArrays(1, &_VAO);
    }

    void Gen()
    {
        glGenVertexArrays(1, &_VAO);
    }

    void Bind()
    {
        glBindVertexArray(_VAO);
    }

    void Unbind()
    {
        glBindVertexArray(0);
    }

    void EnableVertexAttribute(unsigned short vertexAttributeNo, unsigned short objectsInCurrentAttribute, unsigned short objectsInSingleVertex)
    {
        glVertexAttribPointer(vertexAttributeNo, objectsInCurrentAttribute, GL_FLOAT, GL_FALSE, objectsInSingleVertex * sizeof(GLfloat), (void*)(3*vertexAttributeNo * sizeof(GLfloat)));
        glEnableVertexAttribArray(vertexAttributeNo);
    }

    GLuint &GetVAO()
    {
        return _VAO;
    }

private:
    GLuint _VAO;
    //unsigned short objectsInSingleVertex;
};



