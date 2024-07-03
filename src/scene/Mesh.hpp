#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

#include <string>
#include <vector>


namespace Synapse
{

class Mesh
{
public:

    Mesh() = default;

    Mesh(const std::string &verticiesFilePath, const std::string &indiciesFilePath){}

    Mesh(float *verticiesData, unsigned int totalVerticies, unsigned int *indiciesData, unsigned int totalIndicies)
    :    _verticiesData(verticiesData), _totalVerticies(totalVerticies),
         _indiciesData(indiciesData), _totalIndicies(totalIndicies)
    {
        std::cout << "Initializing the mesh!" << '\n';
    }

    Mesh(std::vector<float> &verticiesData, std::vector<unsigned int> &indiciesData)
    :    _verticiesData(&verticiesData[0]), _totalVerticies(verticiesData.size()),
         _indiciesData(&indiciesData[0]), _totalIndicies(indiciesData.size()){}










//    Mesh(float *verticiesData, unsigned int totalVerticies, unsigned int *indiciesData, unsigned int totalIndicies)
//    :    _VB(totalVerticies, verticiesData),
//         _EB(totalIndicies, indiciesData){}

//    Mesh(std::vector<float> &verticiesData, std::vector<unsigned int> &indiciesData)
//    :    _VB(verticiesData.size(), &verticiesData[0]),
//         _EB(indiciesData.size(), &indiciesData[0]){}


    void LoadVerticies(const std::string &filePath);
    void LoadIndicies(const std::string &filePath);

    ~Mesh() = default;


//private:

    float *_verticiesData = nullptr;
    unsigned int _totalVerticies = 0;
    unsigned int *_indiciesData = nullptr;
    unsigned int _totalIndicies = 0;


    struct VertexArray    _VA;
    struct VertexBuffer   _VB;
    struct IndexBuffer    _EB;

};


}