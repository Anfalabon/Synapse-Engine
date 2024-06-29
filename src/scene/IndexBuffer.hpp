#pragma once

#include <glad/glad.hpp>

#include <iostream>
#include <array>
#include <vector>




struct IndexBuffer
{
    IndexBuffer() = default;
    IndexBuffer(GLuint totalIndicies, GLuint *indiciesData)
            :    _totalIndicies(totalIndicies),
                 _indiciesData(std::move(indiciesData)){}

    ~IndexBuffer()
    {
        glDeleteBuffers(1, &_EBO);
        if(_indiciesData!=nullptr)
        {
            delete[] _indiciesData;
            //delete[] (GLuint*)_indiciesData;
        }
    }

    void SetIndicies(GLuint totalIndicies, GLuint *indiciesData)
    {
        _totalIndicies = totalIndicies;
        _indiciesData = std::move(indiciesData);
    }

    void Gen()
    {
        glGenBuffers(1, &_EBO);
    }

    void Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*_totalIndicies, _indiciesData, GL_STATIC_DRAW);
    }

    void Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLuint &GetEBO()
    {
        return _EBO;
    }

    GLuint GetTotalIndicies()
    {
        return _totalIndicies;
    }

    GLuint *GetIndiciesData()
    {
        //return (GLuint*)_indiciesData;
        return _indiciesData;
    }

private:
    GLuint _EBO;
    GLuint _totalIndicies;
    GLuint *_indiciesData;
};
