#pragma once

#include <glad/glad.hpp>

#include "Buffer.hpp"
#include "../debug/LOG.hpp"

#include <iostream>
#include <array>
#include <vector>

namespace Synapse
{

class IndexBuffer
{
public:
    IndexBuffer() = default;
    IndexBuffer(GLuint totalIndicies, GLuint *indiciesData)
    :   _totalIndicies(totalIndicies),
        _indiciesData(indiciesData){}

    ~IndexBuffer()
    {
        DEBUG("Running IndexBuffer destructor!");
        glDeleteBuffers(1, &_EBO);
        //#define __DELETE__BUFFER__
        #ifdef __DELETE__BUFnFER__
        if(_indiciesData!=nullptr)
        {
            delete[] _indiciesData;
        }
        #endif
        DEBUG("Completed running IndexBuffer destructor!");
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

