#pragma once

#include <iostream>
#include <vector>


typedef unsigned int GLuint;


class Renderer
{
public:
    Renderer() = default;
    ~Renderer() = default;

    void _zBufferBg(float r, float g, float b, float w);

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
    std::vector<std::size_t> pixels;
};






void Renderer::_zBufferBg(float r, float g, float b, float w)
{

}




void Entity
