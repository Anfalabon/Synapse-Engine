#pragma once

#include "ModelsData.hpp"

#include <vector>
#include <unordered_map>


namespace Synapse
{

class ModelData
{
public:

    ModelData() = default;
    ModelData(Vertex *verticiesData, unsigned int totalVerticies, unsigned int *indiciesData, unsigned int totalIndicies)
            : _verticiesData(verticiesData), _totalVerticies(totalVerticies),
              _indiciesData(indiciesData), _totalIndicies(totalIndicies){}
    ~ModelData() = default;

    Vertex *_verticiesData;
    unsigned int _totalVerticies;
    unsigned int *_indiciesData;
    unsigned int _totalIndicies;
};


struct Model
{
    const std::string name;
    ModelData md;
    //static Model GetModelData(const std::string &modelName);
};



inline Model GetModel(const std::string &modelName)
{
    using namespace modelsData;
    if(modelName == "Cube")
    {
        return {modelName, ModelData(cubeVerticiesData, cubeTotalVerticies, cubeIndiciesData, cubeTotalIndicies)};
    }
    else if(modelName == "Ground")
    {
        return {modelName, ModelData(groundVerticiesData, groundTotalVerticies, groundIndiciesData, groundTotalVerticies)};
    }
    else if(modelName == "Trapizoid")
    {
        return {modelName, ModelData(trapizoidVerticiesData, trapizoidTotalVerticies, trapizoidIndiciesData, trapizoidTotalIndicies)};
    }
    else if(modelName == "Pyramid")
    {
        return {modelName, ModelData(pyramidVerticesData, pyramidTotalVerticies, pyramidIndicesData, pyramidTotalIndicies)};
    }

    return {modelName, ModelData()};
}


//inline std::unordered_map<std::string, Model> model = {{"Cube", Model(modelsData::cubeVerticiesData, modelsData::cubeTotalVerticies, modelsData::cubeIndiciesData, modelsData::cubeTotalIndicies)}};

//model["Cube"] = Model(modelsData::cubeVerticiesData, modelsData::cubeTotalVerticies, modelsData::cubeIndiciesData, modelsData::cubeTotalIndicies);


}







