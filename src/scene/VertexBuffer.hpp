#pragma once

#include <glad/glad.hpp>

#include <iostream>
#include <array>
#include <vector>



namespace Synapse
{


struct VertexBuffer
{
    VertexBuffer() = default;

    VertexBuffer(GLuint totalVerticies, float *verticiesData)
    : _totalVerticies(totalVerticies),
      _verticiesData(verticiesData){}

    ~VertexBuffer()
    {
        glDeleteBuffers(1, &_VBO);
        if (_verticiesData != nullptr)
        {
            delete[] _verticiesData;
        }
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