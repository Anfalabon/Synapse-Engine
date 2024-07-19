#pragma once


#include <glad/glad.hpp>

#include "scene/Scene.hpp"
#include "shader/Shader.hpp"
#include "core/Macros.hpp"
#include "core/Filesystem.hpp"
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


    static __ALWAYS__INLINE__ void GLDraw(const unsigned int totalMeshIndicies)
    {
        glDrawElements(GL_TRIANGLES, totalMeshIndicies, GL_UNSIGNED_INT, 0);
    }

    __ALWAYS__INLINE__ void AddShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        m_sceneShaders.push_back(Shader(vertexShaderPath, fragmentShaderPath));
    }

    __ALWAYS__INLINE__ void SetShader(std::size_t index = 0)
    {
        std::size_t lastIndex = m_sceneShaders.size() - 1;
        m_sceneShaders[lastIndex].Compile();
        m_sceneShaders[lastIndex].AttachAndLink();
        m_sceneShaders[lastIndex].RemoveShaders();
    }

    __ALWAYS__INLINE__ Shader& GetShader(std::size_t index)
    {
        return m_sceneShaders[index];
        //return (index >= m_sceneShaders.size() || index < 0) ? Shader() : m_sceneShaders[index];
    }

    __ALWAYS__INLINE__ std::size_t GetTotalShaders()
    {
        return m_sceneShaders.size();
    }

    void Render() override;
    static void RenderScenePartially(Scene *scene, std::vector<Shader> &sceneShaders, std::size_t first, std::size_t last);   //this is for the Parallelism
    void Render(Scene *scene, const Shader &sceneShaders = Shader());  //will add std::vector<Shader> sceneShaders

#if defined(__UTILIZE__STANDARDCXX__THREADING___)
    void renderEntitiesPartially(std::size_t start, std::size_t end);
#endif


private:

    Synapse::Scene               *m_scene;
    std::vector<Synapse::Shader>  m_sceneShaders;
    Synapse::Filesystem           m_fileWatcher;

    std::time_t lastModificationTime = 0;

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