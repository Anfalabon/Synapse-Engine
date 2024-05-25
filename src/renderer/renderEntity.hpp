#pragma once

#include <vector>
#include <type_traits>
#include <future>
#include <thread>

#include <glad/glad.hpp>

#include "../entity/Entities.hpp"




class Renderer
{
public:
    Renderer() = default;
    ~Renderer() = default;

    void _zBufferBg(float r, float g, float b, float w);
    virtual void render(){};
};


class EntityRenderer : public Renderer
{
public:

    EntityRenderer() = default;
    EntityRenderer(std::size_t totalEntities)
        :m_totalEntities(totalEntities)
        {
            m_entitiesVAO.reserve(m_totalEntities);
            m_entitiesTotalInidicies.reserve(m_totalEntities);
        }

    inline void initVAO(GLuint VAO){m_entitiesVAO.push_back(VAO);}
    inline void initIndicies(GLuint totalEntityIndicies){m_entitiesTotalInidicies.push_back(totalEntityIndicies);}

    //void renderEntitiesPartially(std::size_t start, std::size_t end);


    void render() override;

private:

    std::size_t m_totalEntities;
    std::vector <GLuint> m_entitiesVAO;
    std::vector <GLuint> m_entitiesTotalInidicies;
};




class ImageRenderer : public Renderer
{
public:
    void render() override;
private:
    std::vector<uint64_t> pixels;
};



