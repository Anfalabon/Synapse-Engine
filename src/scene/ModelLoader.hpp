#pragma once

#include "Mesh.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>


namespace Synapse
{


class ModelLoader
{
public:
    ModelLoader() = default;
    ~ModelLoader() = default;

    std::vector<float> &LoadVerticiesData(const std::string &filePath);
    std::vector<unsigned int> &LoadIndiciesData(const std::string &filePath);


    void CreateFrequentlyLoadedTextures();
    void SetModelsDataMap();
    std::pair<std::string, Synapse::Mesh> GetModel(const std::string &modelName);

private:

    std::unordered_map<std::string, Synapse::Mesh> m_modelsMap;
};



}