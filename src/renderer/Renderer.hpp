#pragma once


#include <glad/glad.hpp>

#include "../scene/Scene.hpp"
#include "shader/Shader.hpp"
//#include "../camera/Camera.hpp"   //camera will be inside the 'Renderer class'(for now the SceneRenderer class) not inside 'Engine'

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
        //return (index >= m_sceneShaders.size() || index < 0) ? Shader() : m_sceneShaders[index];
    }

    std::size_t GetTotalShaders()
    {
        return m_sceneShaders.size();
    }


    void Render() override;
    static void RenderScenePartially(Scene *scene, std::vector<Shader> &sceneShaders, std::size_t first, std::size_t last);   //this is for the Parallelism
    void Render(Scene *scene, Shader *sceneShaders = new Shader());  //will add std::vector<Shader> sceneShaders

#if defined(__UTILIZE__STANDARDCXX__THREADING___)
    void renderEntitiesPartially(std::size_t start, std::size_t end);
#endif


private:

    Synapse::Scene *m_scene;
    std::vector<Synapse::Shader>  m_sceneShaders;
    //std::vector<Camera*> m_cameras;

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