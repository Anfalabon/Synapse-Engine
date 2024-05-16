#pragma once

#include <vector>
#include <glad/glad.hpp>

class Renderer
{
public:
    Renderer(std::size_t totalEntities)
        :m_totalEntities(totalEntities)
        {
            m_entitiesVAO.reserve(m_totalEntities);
            m_entitiesTotalInidicies.reserve(m_totalEntities);
        }

    ~Renderer() = default;

    inline void initVAO(GLuint VAO){m_entitiesVAO.push_back(VAO);}
    inline void initIndicies(GLuint totalEntityIndicies){m_entitiesTotalInidicies.push_back(totalEntityIndicies);}
    void render();

private:
    std::size_t m_totalEntities;

    std::vector <GLuint> m_entitiesVAO;
    std::vector <GLuint> m_entitiesTotalInidicies;
};
