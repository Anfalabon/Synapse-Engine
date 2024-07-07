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

    m_modelsMap["Cube"] = Mesh(cubeVerticiesData, cubeIndiciesData, "../vendor/imageLoader/images/grassTexture.jpg");
    m_modelsMap["Ground"] = Mesh(groundVerticiesData, groundIndiciesData, "../vendor/imageLoader/images/clearRoadTexture.jpg");
    m_modelsMap["Trapizoid"] = Mesh(trapizoidVerticiesData, trapizoidIndiciesData, "../vendor/imageLoader/images/groundTexture.jpg");
    m_modelsMap["Pyramid"] = Mesh(pyramidVerticesData, pyramidIndicesData, "../vendor/imageLoader/images/oceanTexture.jpg");
    m_modelsMap["Cylinder"] = Mesh(cylinderVerticiesData, cylinderIndiciesData, "../vendor/imageLoader/images/oceanTexture.jpg");
    m_modelsMap["Icosphere"] = Mesh(icosphereVerticiesData, icosphereIndiciesData, "../vendor/imageLoader/images/groundTexture.jpg");
    m_modelsMap["Sphere"] = Mesh(sphereVerticiesData, sphereIndiciesData, "../vendor/imageLoader/images/basketballTexture.jpg");
    m_modelsMap["Wall"] = Mesh(wallVerticiesData, wallIndiciesData, "../vendor/imageLoader/images/brickTexture2.jpg");
    m_modelsMap["Door"] = Mesh(doorVerticiesData, doorIndiciesData, "../vendor/imageLoader/images/doorTexture.jpg");
    m_modelsMap["Bullet"] = Mesh(bulletVerticiesData, cylinderIndiciesData, "../vendor/imageLoader/images/clearRoadTexture.jpg");
    m_modelsMap["Black Hole"] = Mesh(interstellerObjectVerticiesData, sphereIndiciesData, "");

    //m_modelsMap["House"] = Mesh(doorVerticiesData, roofVerticiesData, wallVerticiesData, groundVerticiesData,
    //                            doorIndiciesData, roofIndiciesData, wallIndiciesData, groundIndiciesData,
    //                            "doorTexture.jpg", "roofTexture.jpg", "wallTexture.jpg", "groundTexture.jpg");

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