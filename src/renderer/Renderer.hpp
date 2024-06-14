#pragma once

#include <vector>
#include <type_traits>

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
    SceneRenderer(std::size_t totalEntities)
            : m_totalEntities(totalEntities)
    {
        m_entitiesVAO.reserve(m_totalEntities);
        m_entitiesTotalIndicies.reserve(m_totalEntities);
    }
    ~SceneRenderer() = default;

    //really bad code and have to fix it later
    inline void InitVAO(GLuint VAO){m_entitiesVAO.push_back(VAO);}
    inline void InitIndicies(GLuint totalEntityIndicies){m_entitiesTotalIndicies.push_back(totalEntityIndicies);}

    inline std::size_t TotalEntitiesToRender(){return m_totalEntities;}

    void Render() override;
    void Render(Scene *scene);

#if defined(__UTILIZE__STANDARDCXX__THREADING___)
    void renderEntitiesPartially(std::size_t start, std::size_t end);
#endif


private:

    //scene object info

    std::size_t m_totalEntities;
    std::vector <GLuint> m_entitiesVAO;
    std::vector <GLuint> m_entitiesTotalIndicies;

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