#pragma once

#include <vector>
#include <type_traits>
#include <future>
#include <thread>

#include <glad/glad.hpp>

#include "../entity/Entities.hpp"


//class EntityRenderer
//{
//public:
//    void render();
//private:
//    std::size_t m_totalEntities;
//    std::vector <GLuint> m_entitiesVAO;
//    std::vector <GLuint> m_entitiesTotalInidicies;
//};


//class ImageRenderer
//{
//public:
//    void render();
//private:
//    std::vector<uint64_t> pixels;
//};


class Renderer
{
public:
    Renderer() = default;
    Renderer(std::size_t totalEntities)
        :m_totalEntities(totalEntities)
        {
            m_entitiesVAO.reserve(m_totalEntities);
            m_entitiesTotalInidicies.reserve(m_totalEntities);
        }

    ~Renderer() = default;

    inline void initVAO(GLuint VAO){m_entitiesVAO.push_back(VAO);}
    inline void initIndicies(GLuint totalEntityIndicies){m_entitiesTotalInidicies.push_back(totalEntityIndicies);}

    void _zBufferBg(float r, float g, float b, float w);
    void renderEntitiesPartially(std::size_t start, std::size_t end);
    void renderEntities();
//    void renderImage();



    //virtual void render() = 0;

//    inline EntityRenderer& entityRenderer(){return e_renderer;}
//    inline ImageRenderer& imageRenderer(){return i_renderer;}

private:
    std::size_t m_totalEntities;
    std::vector <GLuint> m_entitiesVAO;
    std::vector <GLuint> m_entitiesTotalInidicies;


//    std::vector<uint64_t> pixels;
//
//public:
//    EntityRenderer e_renderer;
//    ImageRenderer i_renderer;



};


//class EntityRenderer : Renderer
//{
//public:
//    void render() override;
//
//private:
//    std::size_t m_totalEntities;
//
//    std::vector <GLuint> m_entitiesVAO;
//    std::vector <GLuint> m_entitiesTotalInidicies;
//};


//class ImageRenderer : Renderer
//{
//public:
//    void render() override;
//private:
//    std::vector<uint64_t> pixels;
//};



