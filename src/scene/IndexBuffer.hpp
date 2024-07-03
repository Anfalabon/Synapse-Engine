#pragma once

#include <glad/glad.hpp>

#include <iostream>
#include <array>
#include <vector>

namespace Synapse
{

struct IndexBuffer
{
    IndexBuffer() = default;
    IndexBuffer(GLuint totalIndicies, GLuint *indiciesData)
    :    _totalIndicies(totalIndicies),
         _indiciesData(indiciesData){}

    ~IndexBuffer()
    {
        glDeleteBuffers(1, &_EBO);
        if(_indiciesData!=nullptr)
        {
            delete[] _indiciesData;
        }
    }

    void SetIndicies(GLuint totalIndicies, GLuint *indiciesData);
    void Gen();
    void Bind();
    void Unbind();
    GLuint &GetEBO(){return _EBO;}
    GLuint GetTotalIndicies(){return _totalIndicies;}
    GLuint *GetIndiciesData(){return _indiciesData;}

//private:
    GLuint _EBO;
    GLuint _totalIndicies;
    GLuint *_indiciesData = nullptr;    //not initializing this pointer to nullptr caused an error
};




}

