#pragma once

#include <glad/glad.hpp>

#include "scene/Buffer.hpp"
#include "debug/LOG.hpp"

#include <iostream>
#include <array>
#include <vector>

namespace Synapse
{

class VertexBuffer
{
public:
    VertexBuffer() = default;
    VertexBuffer(GLuint totalVerticies, float *verticiesData)
    :   _totalVerticies(totalVerticies),
        _verticiesData(verticiesData){}

    ~VertexBuffer()
    {
        DEBUG("Running VertexBuffer destructor!");
        //glDeleteBuffers(1, &_VBO);
        //#define __DELETE__BUFFER__
        #ifdef __DELETE__BUFFER__
        if (_verticiesData != nullptr)
        {
            delete[] _verticiesData;
        }
        #endif
        DEBUG("Completed running VertexBuffer destructor!");
    }

    void SetVerticies(GLuint totalVerticies, float *verticiesData);
    void Gen();
    void Bind();
    void Unbind();
    GLuint &GetVBO(){return _VBO;}
    GLuint GetTotalVerticies(){return _totalVerticies;}
    float *GetVerticiesData(){return _verticiesData;}

//private:
    GLuint _VBO;
    GLuint _totalVerticies;
    //std::vector<float> _verticiesData;
    float *_verticiesData = nullptr;    //not initializing this pointer to nullptr caused an error
};


}