#include "renderEntity.hpp"

#include <glad/glad.hpp>


Renderer::Renderer()
{
    //initialize the Entities info's

    m_entitesVAO = new GLuint[m_totalEntities];
    m_entitiesTotalInidicies = new GLuint[m_totalEntities];
}


//rendering like this is much faster as we are storing the entities infos' in a contiguous memory.
//with this CPU's L1 cahce memroy get's more chance to deal with faster accessing
void Renderer::render()
{
    for(std::size_t i=0; i<m_totalEntities; ++i)
    {
        glBindVertexArray(m_entitiesVAO[i]);
        glDrawElements(GL_TRIANGLES, m_entitiesTotalInidicies[i], GL_UNSIGNED_INT, 0);
    }
}


~Renderer::Renderer()
{
    delete[] m_entitesVAO;
    delete[] m_entitiesTotalInidicies;
}