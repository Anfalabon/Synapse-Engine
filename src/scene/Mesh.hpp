#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "../renderer/Texture.hpp"
#include "../debug/LOG.hpp"

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

#else

    Mesh(float *verticiesData, unsigned int totalVerticies, unsigned int *indiciesData, unsigned int totalIndicies, const char *textureFilePath = "")
    :    _VB(totalVerticies, verticiesData),
         _EB(totalIndicies, indiciesData),
         _texture(textureFilePath){}

    Mesh(std::vector<float> &verticiesData, std::vector<unsigned int> &indiciesData, const char *textureFilePath = "")
    :    _VB(verticiesData.size(), &verticiesData[0]),
         _EB(indiciesData.size(), &indiciesData[0]),
         _texture(textureFilePath)
         {
             DEBUG("Constructing Mesh...");
         }

#endif

    void LoadVerticies(const std::string &filePath);
    void LoadIndicies(const std::string &filePath);

    ~Mesh() = default;


//private:

//    float *_verticiesData = nullptr;
//    unsigned int _totalVerticies = 0;
//    unsigned int *_indiciesData = nullptr;
//    unsigned int _totalIndicies = 0;


    VertexArray    _VA;
    VertexBuffer   _VB;
    IndexBuffer    _EB;
    Texture        _texture;

};


}