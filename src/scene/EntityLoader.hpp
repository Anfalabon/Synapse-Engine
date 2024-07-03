#pragma once

#include "Mesh.hpp"
#include "ModelsData.hpp"
//#include "ModelsDataVector.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>


namespace Synapse
{



//ModelLoader *modelLoader = new ModelLoader();
//
//g_modelMap["Cube"] = Model(modelLoader->LoadVerticies("filePath", "txt"), modelLoader->LoadIndicies("filePath", "txt"));
//
////do error checking eg. if the models verticies and indicies data's were loaded correctly
//
//delete modelLoader;



struct Model
{
    const std::string name;
    Mesh md;
};

//inline std::unordered_map<std::string, std::vector<Mesh>> g_modelMap;
inline std::unordered_map<std::string, Mesh> g_modelMap;


inline void SetModelsMapData()
{
    //g_modelMap["Cube"] = Mesh("../src/scene/models/sphere/verticies.txt", "../src/scene/models/sphere/indicies.txt");
#if 0

    g_modelMap["House"] = Mesh();
    g_modelMap["Cube"] = Mesh(cubeVerticiesData, cubeIndiciesData);
    g_modelMap["Ground"] = Mesh(groundVerticiesData, groundIndiciesData);
    g_modelMap["Trapizoid"] = Mesh(trapizoidVerticiesData, trapizoidIndiciesData);
    g_modelMap["Pyramid"] = Mesh(pyramidVerticesData, pyramidIndicesData);
    g_modelMap["Cylinder"] = Mesh(cylinderVerticiesData, cylinderIndiciesData);
    g_modelMap["Icosphere"] = Mesh(icosphereVerticiesData, icosphereIndiciesData);
    g_modelMap["Sphere"] = Mesh(sphereVerticiesData, sphereIndiciesData);
//    g_modelMap["Street Light"] = Mesh(cubeVerticiesData, cubeIndiciesData), Mesh(cylinderVerticiesData, cylinderIndiciesData);

#else

    //std::cout << "Cube is going to load..." << '\n';

    //Mesh m = Mesh();

    g_modelMap["house"] = Mesh();

    g_modelMap["Cube"] = Mesh(cubeVerticiesData, cubeTotalVerticies, cubeIndiciesData, cubeTotalIndicies);
    g_modelMap["Ground"] = Mesh(groundVerticiesData, groundTotalVerticies, groundIndiciesData, groundTotalIndicies);
    g_modelMap["Trapizoid"] = Mesh(trapizoidVerticiesData, trapizoidTotalVerticies, trapizoidIndiciesData, trapizoidTotalIndicies);
    g_modelMap["Pyramid"] = Mesh(pyramidVerticesData,  pyramidTotalVerticies, pyramidIndicesData, pyramidTotalIndicies);
    g_modelMap["Cylinder"] = Mesh(cylinderVerticiesData, cylinderTotalVerticies, cylinderIndiciesData, cylinderTotalIndicies);
    g_modelMap["Icosphere"] = Mesh(icosphereVerticiesData, icosphereTotalVerticies, icosphereIndiciesData, icosphereTotalIndicies);
    g_modelMap["Sphere"] = Mesh(sphereVerticiesData, sphereTotalVerticies, sphereIndiciesData, sphereTotalIndicies);


#endif
}



inline Model GetModel(const std::string &modelName)
{
    if(g_modelMap.begin() != g_modelMap.end())
    {
        return {modelName, g_modelMap[modelName]};
    }
    return {modelName, Mesh()};
}


inline Mesh GetMeshes(const std::string &modelsName)
{
    if(g_modelMap.begin() != g_modelMap.end())
    {
        return g_modelMap[modelsName];
    }
    return Mesh();
}




//#include <iostream>
//#include <vector>
//#include <unordered_map>
//
//
//class Mesh
//{
//public:
//    Mesh(const std::string &&){};
//    ~Mesh() = default;
//};
//
//
//inline std::unordered_map<std::string, std::vector<Mesh>> g_modelsMap;
//
//
//void SetModelsMap()
//{
//    g_modelsMap["Cube"] = {Mesh("Cube")};
//    g_modelsMap["House"] = {Mesh("Ground"), Mesh("Door"), Mesh("Balcony"), Mesh("Tree"), Mesh("Roof")};
//}
//
//
//std::vector<Mesh> GetMeshes(const std::string &modelName)
//{
//    if(g_modelsMap.begin() != g_modelsMap.end())
//    {
//        return g_modelsMap[modelName];
//    }
//    return {};
//}
//
//
//class GameObject
//{
//public:
//    GameObject() = default;
//    explicit GameObject(const std::vector<Mesh> &&meshes)
//    {
//        m_meshes = std::move(meshes);
//    }
//    ~GameObject() = default;
//private:
//    std::vector<Mesh> m_meshes;
//};
//
//
//int main()
//{
//    SetModelsMap();
//    GameObject *house = new GameObject(GetMeshes("House"));
//
//    delete house;
//
//    return 0;
//}





}







