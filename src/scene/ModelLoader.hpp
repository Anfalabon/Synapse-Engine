#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace Synapse
{


class Model
{
public:
    Model() = default;
    ~Model() = default;

    void SetName();
    void GetVerticiesData(const std::string &verticiesFilePath);
    void GetIndiciesData(const std::string &indiciesFilePath);

private:

    const std::string name;

    float *_verticies;
    GLuint *_indicies;
};


//
//void LoadModel(const std::string &modelName)
//{
//    Model cube;
//    cube.SetName(modelName);
//    cube.GetVerticiesData();
//    cube.GetIndiciesData();
//    cube.VerticiesData();
//    cube.IndiciesData();
//
//
//
//}




}