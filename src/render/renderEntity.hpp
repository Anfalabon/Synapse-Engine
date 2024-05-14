#pragma once

#include <iostream>
#include <vector>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void render();

private:
    std::size_t m_totalEntities;

    GLuint *m_entitesVAO;
    GLuint *m_entitiesTotalInidicies;

//    std::vector <GLuint> m_entitiesVAO;
//    std::vector <GLuint> m_entitiesTotalInidicies;

};
