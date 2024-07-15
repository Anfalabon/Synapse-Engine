#pragma once

#include "scene/VertexBuffer.hpp"
#include "scene/IndexBuffer.hpp"
#include "renderer/VertexArray.hpp"
#include "renderer/Texture.hpp"
#include "debug/LOG.hpp"

#include <string>
#include <vector>


namespace Synapse
{

class Mesh
{
public:

    Mesh() = default;

    Mesh(const std::string &verticiesFilePath, const std::string &indiciesFilePath){}

#if 0

    Mesh(float *verticiesData, unsigned int totalVerticies, unsigned int *indiciesData, unsigned int totalIndicies, const char *textureFilePath = "")
    :    _verticiesData(verticiesData), _totalVerticies(totalVerticies),
         _indiciesData(indiciesData), _totalIndicies(totalIndicies),
         _texture(textureFilePath)
    {
        std::cout << "Initializing the mesh!" << '\n';
    }

    Mesh(std::vector<float> &verticiesData, std::vector<unsigned int> &indiciesData, const char *textureFilePath = "")
    :    _verticiesData(&verticiesData[0]), _totalVerticies(verticiesData.size()),
         _indiciesData(&indiciesData[0]), _totalIndicies(indiciesData.size()),
         _texture(textureFilePath){}

#endif


#if 0

    Mesh(float *verticiesData, unsigned int totalVerticies, unsigned int *indiciesData, unsigned int totalIndicies, const char *textureFilePath = "")
    :    _VB(totalVerticies, verticiesData),
         _EB(totalIndicies, indiciesData),
         _texture(textureFilePath)
    {

    }

    Mesh(std::vector<float> &verticiesData, std::vector<unsigned int> &indiciesData, const char *textureFilePath = "")
    :    _VB(verticiesData.size(), &verticiesData[0]),
         _EB(indiciesData.size(), &indiciesData[0]),
         _texture(textureFilePath)
    {
        DEBUG("Constructing Mesh...");
    }

    Mesh(std::vector<float> &verticiesData, std::vector<unsigned int> &indiciesData, unsigned char *imageData, int width, int height, int nrChannels)
    :    _VB(verticiesData.size(), &verticiesData[0]),
         _EB(indiciesData.size(), &indiciesData[0]),
         _texture(imageData, width, height, nrChannels)
    {
        DEBUG("Constructing Mesh...");
    }

    Mesh(std::vector<float> &verticiesData, std::vector<unsigned int> &indiciesData, const Texture &texture)
            :    _VB(verticiesData.size(), &verticiesData[0]),
                 _EB(indiciesData.size(), &indiciesData[0]),
                 _texture(texture.m_imageData, texture.m_width, texture.m_height, texture.m_nrChannels)
    {
        DEBUG("Constructing Mesh...");
    }

#endif



    Mesh(const std::vector<float> &verticiesData,
         const std::vector<unsigned int> &indiciesData,
         const char *textureFilePath = "")
    :   _VB(verticiesData),
        _EB(indiciesData),
        _texture(textureFilePath)
    {
        DEBUG("Constructing Mesh(With New Texture)...");
        //S_PAUSE_FOR_READING();
    }



    Mesh(const std::vector<float> &verticiesData,
         const std::vector<unsigned int> &indiciesData,
         const Texture &texture)
    :   _VB(verticiesData),
        _EB(indiciesData),
        _texture(texture.m_imageData, texture.m_width, texture.m_height, texture.m_nrChannels)
    {
        DEBUG("Constructing Mesh(With Old Texture)...");
        //S_PAUSE_FOR_READING();
    }


    void LoadVerticies(const std::string &filePath);
    void LoadIndicies(const std::string &filePath);


    ~Mesh() = default;


//private:

//    float *_verticiesData = nullptr;
//    unsigned int _totalVerticies = 0;
//    unsigned int *_indiciesData = nullptr;
//    unsigned int _totalIndicies = 0;


    Synapse::VertexArray    _VA;
    Synapse::VertexBuffer   _VB;
    Synapse::IndexBuffer    _EB;
    Synapse::Texture        _texture;    //will make it an std::vector<Texture> if needed

};


}