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

//       for(const Shader &sceneShader : m_sceneShaders)
//       {
//           sceneShader.RemoveProgram();
//       }
    }

    __ALWAYS__INLINE__ void AddShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        m_sceneShaders.push_back(Shader(vertexShaderPath, fragmentShaderPath));
    }

    __ALWAYS__INLINE__ Shader& GetShader(std::size_t index)
    {
        return m_sceneShaders[index];
        //return (index >= m_sceneShaders.size() || index < 0) ? Shader() : m_sceneShaders[index];
    }

    __ALWAYS__INLINE__ std::size_t GetTotalShaders() const {return m_sceneShaders.size();}


    void Render() override{}
    void Render(Scene *scene, const SceneCamera &camera, const Shader &sceneShaders = Shader());  //will add std::vector<Shader> sceneShaders

private:

    static __ALWAYS__INLINE__ void GLDraw(const unsigned int totalMeshIndicies)
    {
        glDrawElements(GL_TRIANGLES, totalMeshIndicies, GL_UNSIGNED_INT, 0);
    }

private:

    std::vector<Synapse::Shader>  m_sceneShaders;
    Synapse::Filesystem           m_fileWatcher;

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





class FontRenderer : public Renderer
{
public:
    FontRenderer() = default;
    ~FontRenderer() = default;

    void Render() override;

private:

};





}