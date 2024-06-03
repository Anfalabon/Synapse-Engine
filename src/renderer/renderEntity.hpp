#pragma once

#include <vector>
#include <type_traits>
#include <future>
#include <thread>

#include <glad/glad.hpp>

#include "../entity/Entities.hpp"


//#define __UTILIZE__STANDARDCXX__THREADING___

namespace Synapse
{

class Renderer
{
public:
    Renderer() = default;
    virtual ~Renderer() = default;

    void _zBufferBg(float r, float g, float b, float w);


//    virtual inline void InitVAO(GLuint VAO) = 0;
//    virtual inline void InitIndicies(GLuint totalEntityIndicies) = 0;
    virtual void Render() = 0;
};


class EntityRenderer : public Renderer
{
public:

    EntityRenderer() = default;
    EntityRenderer(std::size_t totalEntities)
            : m_totalEntities(totalEntities)
    {
        m_entitiesVAO.reserve(m_totalEntities);
        m_entitiesTotalInidicies.reserve(m_totalEntities);
    }
    ~EntityRenderer() = default;

    inline void InitVAO(GLuint VAO){m_entitiesVAO.push_back(VAO);}
    inline void InitIndicies(GLuint totalEntityIndicies){m_entitiesTotalInidicies.push_back(totalEntityIndicies);}
    void Render() override;

#if defined(__UTILIZE__STANDARDCXX__THREADING___)
    void renderEntitiesPartially(std::size_t start, std::size_t end);
#endif


private:

    std::size_t m_totalEntities;
    std::vector <GLuint> m_entitiesVAO;
    std::vector <GLuint> m_entitiesTotalInidicies;
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