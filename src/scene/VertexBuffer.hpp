#pragma once

#include <glad/glad.hpp>

#include <iostream>
#include <array>
#include <vector>



template<class T> struct VertexBuffer
{
    VertexBuffer() = default;
    VertexBuffer(GLuint totalVerticies, T *verticiesData)
            :     _totalVerticies(totalVerticies),
                  _verticiesData(verticiesData){}

    ~VertexBuffer()
    {
        glDeleteBuffers(1, &_VBO);
        if(_verticiesData!=nullptr)
        {
            delete[] _verticiesData;
            //delete[] (Vertex*)_verticiesData;
        }
    }

    void SetVerticies(GLuint totalVerticies, T *verticiesData)
    {
        _totalVerticies = totalVerticies;
        _verticiesData = std::move(verticiesData);
    }

    void Gen()
    {
        glGenBuffers(1, &_VBO);
    }

    void Bind()
    {
        //_verticiesData = &_vVerticiesData[0];
        unsigned long TARGET_BUFFER = 0x8892;   //GL_ARRAY_BUFFER
        glBindBuffer(TARGET_BUFFER, _VBO);
        glBufferData(TARGET_BUFFER, sizeof(T)*_totalVerticies, _verticiesData, GL_STATIC_DRAW);
    }

    void Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint &GetVBO()
    {
        return _VBO;
    }

    GLuint GetTotalVerticies()
    {
        return _totalVerticies;
    }

    T *GetVerticiesData()
    {
        //return (Vertex*)_verticiesData;
        return _verticiesData;
    }

private:
    GLuint _VBO;
    GLuint _totalVerticies;
    T *_verticiesData;
};
