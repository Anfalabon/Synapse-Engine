#pragma once

#include "scene/Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

    void CreateFrequentlyLoadedTextures();
    void SetModelsDataMap();
    std::pair<std::string, Synapse::Mesh> GetModel(const std::string &modelName);

    void LoadUsingAssimp(const std::string &filePath);
    void ProcessNode(aiNode *node, const aiScene *scene);
    void ProcessMesh(aiMesh *mesh, const aiScene *scene);

private:

    std::unordered_map<std::string, Synapse::Mesh> m_modelsMap;
};



}