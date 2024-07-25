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
    std::pair<std::string, std::vector<Synapse::Mesh>> GetModel(const std::string &modelName);

    std::vector<Synapse::Mesh> LoadUsingSynapse(const std::vector<float> &verticies,
                                                const std::vector<unsigned int> &indicies,
                                                const Texture &textureFilePath);

    void ProcessVerticies(Mesh &currentMesh, aiMesh *mesh);
    void ProcessIndicies(Mesh &currentMesh, aiMesh *mesh);

    std::vector<Synapse::Mesh> LoadUsingAssimp(const std::string &filePath);
    void ProcessNode(aiNode *node, const aiScene *scene);
    void ProcessMesh(aiMesh *mesh, const aiScene *scene);

private:

    std::unordered_map<std::string, std::vector<Synapse::Mesh>> m_modelsMap;

    Texture _t1; //temp
    Texture _t2; //temp

};



}