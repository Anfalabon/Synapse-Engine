#pragma once

#include <glad/glad.hpp>

#include "scene/Buffer.hpp"
#include "debug/Log.hpp"
#include "core/Macros.hpp"

#include <iostream>
#include <array>
#include <vector>

namespace Synapse
{


//#undef __DEBUG__


class IndexBuffer
{
public:
    IndexBuffer() = default;

    IndexBuffer(const std::vector<unsigned int> &indiciesData)
    :   _indiciesData(indiciesData){}


//    IndexBuffer(GLuint totalIndicies, GLuint *indiciesData)
//    :   _totalIndicies(totalIndicies),
//        _indiciesData(indiciesData){}


    ~IndexBuffer()
    {
        DEBUG("Running IndexBuffer destructor!");
        glDeleteBuffers(1, &_EBO);
        DEBUG("Completed running IndexBuffer destructor!");
    }

    void SetIndicies(GLuint totalIndicies, GLuint *indiciesData);
    void Gen();
    void Bind();
    void Unbind();
    GLuint &GetEBO(){return _EBO;}
    //GLuint GetTotalIndicies(){return _totalIndicies;}
    //GLuint *GetIndiciesData(){return _indiciesData;}
    __ALWAYS__INLINE__ std::size_t GetTotalIndicies(){return _indiciesData.size();}
    __ALWAYS__INLINE__ std::vector<unsigned int> GetIndiciesData(){return _indiciesData;}

//private:
    GLuint _EBO;
    GLuint _totalIndicies;
    std::vector<unsigned int> _indiciesData;
    //GLuint *_indiciesData = nullptr;    //not initializing this pointer to nullptr caused an error
};




}

