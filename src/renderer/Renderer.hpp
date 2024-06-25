#pragma once


#include <glad/glad.hpp>

#include "../scene/Scene.hpp"
#include "shader/Shader.hpp"

#include <vector>
#include <unordered_map>



//#define __UTILIZE__STANDARDCXX__THREADING___

namespace Synapse
{


class Renderer
{
public:
    Renderer() = default;
    virtual ~Renderer() = default;

    void _zBufferBg(float r, float g, float b, float w);

    void UseZbuffer();
    void SetBackGround(float r, float g, float b, float w);

    virtual void Render() = 0;
//    void Render(Scene *scene);
};




class SceneRenderer : public Renderer
{
public:

    SceneRenderer() = default;
    ~SceneRenderer()
    {
       for(std::size_t i=0; i<m_sceneShaders.size(); ++i)
       {
           m_sceneShaders[i].RemoveProgram();
       }
    }

    void AddShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        m_sceneShaders.push_back(Shader(vertexShaderPath, fragmentShaderPath));
    }

    void SetShader()
    {
        std::size_t lastIndex = m_sceneShaders.size() - 1;
        m_sceneShaders[lastIndex].Compile();
        m_sceneShaders[lastIndex].AttachAndLink();
        m_sceneShaders[lastIndex].RemoveShaders();
    }

    Shader& GetShader(std::size_t index)
    {
        return m_sceneShaders[index];
    }


    void Render() override;
    void Render(Scene *scene);  //will add std::vector<Shader> sceneShaders

#if defined(__UTILIZE__STANDARDCXX__THREADING___)
    void renderEntitiesPartially(std::size_t start, std::size_t end);
#endif


private:

    Scene *m_scene;
    //std::unordered_map<std::string, Shader> m_sceneShadersMap;
    std::vector<Shader> m_sceneShaders;

};






class ImageRenderer : public Renderer
{
public:
    ImageRenderer() = default;
    ~ImageRenderer() = default;

    void Render() override;

private:
    std::vector <uint64_t> pixels;
};


}