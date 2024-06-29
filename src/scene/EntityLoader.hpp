#pragma once

#include "ModelsDataFloat.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


namespace Synapse
{


template<class T> class ModelData
{
public:

    ModelData() = default;
    ModelData(T *verticiesData, unsigned int totalVerticies, unsigned int *indiciesData, unsigned int totalIndicies)
            : _verticiesData(verticiesData), _totalVerticies(totalVerticies),
              _indiciesData(indiciesData), _totalIndicies(totalIndicies){}
    ~ModelData() = default;

    T *_verticiesData;
    unsigned int _totalVerticies;
    unsigned int *_indiciesData;
    unsigned int _totalIndicies;
};


template<class T> struct Model
{
    const std::string name;
    ModelData<T> md;
};

inline std::unordered_map<std::string, ModelData<float>> g_modelMap;



template<typename U=float> inline void SetModelsMapData()
{
    g_modelMap["Cube"] = ModelData<U>(vCubeVerticiesData.data(), vCubeVerticiesData.size(), cubeIndiciesData, cubeTotalIndicies);
    g_modelMap["Ground"] = ModelData<U>(groundVerticiesData, groundTotalVerticies, groundIndiciesData, groundTotalIndicies);
    g_modelMap["Trapizoid"] = ModelData<U>(trapizoidVerticiesData, trapizoidTotalVerticies, trapizoidIndiciesData, trapizoidTotalIndicies);
    g_modelMap["Pyramid"] = ModelData<U>(pyramidVerticesData,  pyramidTotalVerticies, pyramidIndicesData, pyramidTotalIndicies);
    g_modelMap["Cylinder"] = ModelData<U>(cylinderVerticiesData, cylinderTotalVerticies, cylinderIndiciesData, cylinderTotalIndicies);
    g_modelMap["Icosphere"] = ModelData<U>(icosphereVerticiesData, icosphereTotalVerticies, icosphereIndiciesData, icosphereTotalIndicies);
    g_modelMap["Sphere"] = ModelData<U>(sphereVerticiesData, sphereTotalVerticies, sphereIndiciesData, sphereTotalIndicies);
}


template<typename U=float> inline Model<U> GetModel(const std::string &modelName)
{
    //return {modelName, g_modelMap[modelName]};
    if(g_modelMap.begin() != g_modelMap.end())
    {
        return {modelName, g_modelMap[modelName]};
    }
    return {modelName, ModelData<U>()};
}




}







