#pragma once

#include "scene/VertexBuffer.hpp"
#include "scene/IndexBuffer.hpp"
#include "renderer/VertexArray.hpp"
#include "renderer/Texture.hpp"
#include "debug/Log.hpp"

#include <string>
#include <vector>


namespace Synapse
{


#undef __DEBUG__

class Mesh
{
public:

    Mesh() = default;

    Mesh(const std::vector<float> &verticiesData,
         const std::vector<unsigned int> &indiciesData,
         const char *textureFilePath = "")
    :   m_VB(verticiesData),
        m_EB(indiciesData),
        m_texture(textureFilePath)
    {
        DEBUG("Constructing Mesh(With New Texture)...");
        //S_PAUSE_FOR_READING();
    }



    Mesh(const std::vector<float> &verticiesData,
         const std::vector<unsigned int> &indiciesData,
         const Texture &texture)
    :   m_VB(verticiesData),
        m_EB(indiciesData),
        m_texture(texture.m_imageData, texture.m_width, texture.m_height, texture.m_nrChannels)
    {
        DEBUG("Constructing Mesh(With Old Texture)...");
        //S_PAUSE_FOR_READING();
    }


    ~Mesh() = default;


    __ALWAYS__INLINE__ std::vector<float> GetVerticiesData(){return m_VB.GetVerticiesData();}
    __ALWAYS__INLINE__ std::size_t GetTotalVerticies(){return m_VB.GetTotalVerticies();}
    __ALWAYS__INLINE__ std::vector<unsigned int> GetIndiciesdata(){return m_EB.GetIndiciesData();}
    __ALWAYS__INLINE__ std::size_t GetTotalIndicies(){return m_EB.GetTotalIndicies();}




//private:


    Synapse::VertexArray    m_VA;
    Synapse::VertexBuffer   m_VB;
    Synapse::IndexBuffer    m_EB;
    Synapse::Texture        m_texture;    //will make it an std::vector<Texture> if needed

};


}