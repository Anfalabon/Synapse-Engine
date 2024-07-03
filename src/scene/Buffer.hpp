#pragma once

#include <glad/glad.hpp>
#include <iostream>


namespace Synapse
{


class Buffer
{
public:
    Buffer() = default;
    virtual ~Buffer() = default;

    virtual void Gen();
    virtual void Bind();
    virtual void Unbind();
    virtual float* GetBufferData(){return data;}
    virtual size_t GetBufferSize(){return size;}

private:
    float *m_data;
    size_t m_size;
    unsigned int m_bufferObject;
    unsigned long m_targetBuffer;
};


}