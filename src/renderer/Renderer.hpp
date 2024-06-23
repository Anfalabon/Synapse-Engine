#pragma once

#include <vector>
#include <unordered_map>

#include <glad/glad.hpp>

#include "../scene/Scene.hpp"




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
    ~SceneRenderer() = default;

    void AddShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        m_sceneShaders.push_back(Shader(vertexShaderPath, fragmentShaderPath));
        D_AddShaderMethodCalled = true;
    }

    void SetShader()
    {
        if(!D_AddShaderMethodCalled)
        {
            std::cout << "Add the shader file first!" << '\n';
            return;
        }

        std::size_t lastIndex = m_sceneShaders.size() - 1;
        m_sceneShaders[lastIndex].Compile();
        m_sceneShaders[lastIndex].AttachAndLink();
        //m_sceneShaders[lastIndex].RemoveShaders();
    }

    Shader& GetShader(std::size_t index)
    {
        return m_sceneShaders[index];
    }


    void Render() override;
    void Render(Scene *scene);

#if defined(__UTILIZE__STANDARDCXX__THREADING___)
    void renderEntitiesPartially(std::size_t start, std::size_t end);
#endif


private:

    Scene *m_scene;
    //std::unordered_map<std::string, Shader> m_sceneShadersMap;
    std::vector<Shader> m_sceneShaders;


    bool D_AddShaderMethodCalled = false;

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