#pragma once

#include <glad/glad.hpp>

#include "scene/Buffer.hpp"
#include "debug/Log.hpp"

#include <iostream>
#include <array>
#include <vector>

namespace Synapse
{


//#undef __DEBUG__

class VertexBuffer
{
public:

    VertexBuffer() = default;

    VertexBuffer(const std::vector<float> &verticiesData)
    :   _verticiesData(verticiesData){}

//    VertexBuffer(GLuint totalVerticies, float *verticiesData)
//    :   _totalVerticies(totalVerticies),
//        _verticiesData(verticiesData){}

    ~VertexBuffer()
    {
        DEBUG("Running VertexBuffer destructor!");
        //glDeleteBuffers(1, &_VBO);
        DEBUG("Completed running VertexBuffer destructor!");
    }

    void SetVerticies(GLuint totalVerticies, float *verticiesData);

    void Gen();
    void Bind();
    void Unbind();

    __ALWAYS__INLINE__ GLuint GetVBO() const {return _VBO;}
    __ALWAYS__INLINE__ std::size_t GetTotalVerticies() const {return _verticiesData.size();}
    __ALWAYS__INLINE__ std::vector<float> GetVerticiesData() const {return _verticiesData;}
    __ALWAYS__INLINE__ void AddVertex(float vertex){_verticiesData.push_back(vertex);}

    //GLuint GetTotalVerticies(){return _totalVerticies;}
    //float *GetVerticiesData(){return _verticiesData;}

private:

    GLuint _VBO;
    std::vector<float> _verticiesData;

    //GLuint _totalVerticies;
    //float *_verticiesData = nullptr;    //not initializing this pointer to nullptr caused an error
};


}