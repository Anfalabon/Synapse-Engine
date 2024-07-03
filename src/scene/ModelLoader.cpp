#include "ModelLoader.hpp"
#include "ModelsDataVector.hpp"
//#include "ModelsData.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


namespace Synapse
{


std::vector<float> LoadVerticiesData(const std::string &filePath)
{
    return {};
}


std::vector<unsigned int> LoadIndiciesData(const std::string &filePath)
{
    return {};
}


void ModelLoader::SetModelsDataMap()
{
    std::cout << "Setting up the models map..." << '\n';

#if 1

    m_modelsMap["Cube"] = Mesh(cubeVerticiesData, cubeIndiciesData);
    m_modelsMap["Ground"] = Mesh(groundVerticiesData, groundIndiciesData);
    m_modelsMap["Trapizoid"] = Mesh(trapizoidVerticiesData, trapizoidIndiciesData);
    m_modelsMap["Pyramid"] = Mesh(pyramidVerticesData, pyramidIndicesData);
    m_modelsMap["Cylinder"] = Mesh(cylinderVerticiesData, cylinderIndiciesData);
    m_modelsMap["Icosphere"] = Mesh(icosphereVerticiesData, icosphereIndiciesData);
    m_modelsMap["Sphere"] = Mesh(sphereVerticiesData, sphereIndiciesData);

#else

    //not calling the default constructor results in memory error
    //will fix this (later: struct VertexArray, struct VertexBuffer, struct IndexBuffer caused the crash!)
    //m_modelsMap[""] = Mesh();

    m_modelsMap["Cube"] = Mesh(cubeVerticiesData, cubeTotalVerticies, cubeIndiciesData, cubeTotalIndicies);
    m_modelsMap["Ground"] = Mesh(groundVerticiesData, groundTotalVerticies, groundIndiciesData, groundTotalIndicies);
    m_modelsMap["Trapizoid"] = Mesh(trapizoidVerticiesData, trapizoidTotalVerticies, trapizoidIndiciesData, trapizoidTotalIndicies);
    m_modelsMap["Pyramid"] = Mesh(pyramidVerticesData,  pyramidTotalVerticies, pyramidIndicesData, pyramidTotalIndicies);
    m_modelsMap["Cylinder"] = Mesh(cylinderVerticiesData, cylinderTotalVerticies, cylinderIndiciesData, cylinderTotalIndicies);
    m_modelsMap["Icosphere"] = Mesh(icosphereVerticiesData, icosphereTotalVerticies, icosphereIndiciesData, icosphereTotalIndicies);
    m_modelsMap["Sphere"] = Mesh(sphereVerticiesData, sphereTotalVerticies, sphereIndiciesData, sphereTotalIndicies);

#endif

}


std::pair<std::string, Mesh> ModelLoader::GetModel(const std::string &modelName)
{
    if(m_modelsMap.begin() != m_modelsMap.end())
    {
        return {modelName, m_modelsMap[modelName]};
    }
    return {modelName, Mesh()};
}








}