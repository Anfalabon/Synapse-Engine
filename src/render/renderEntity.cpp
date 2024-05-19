#include "renderEntity.hpp"

//set the background color
//enable the depth test (z buffer)
//disable the cull face
//clear the color buffer bit along with depth buffer bit
//also the last parameter isn't 'w' (the homogenious coordinate) it's alpha (the opacity)
void Renderer::_zBufferBg(float r, float g, float b, float w)
{
    glClearColor(r, g, b, w);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//rendering like this is much faster as we are storing the entities infos' in a contiguous memory.
//with this CPU's L1 cahce memroy get's more chance to deal with faster accessing
void Renderer::renderEntities()
{
    for(std::size_t i=0; i<m_totalEntities; ++i)
    {
        glBindVertexArray(m_entitiesVAO[i]);
        glDrawElements(GL_TRIANGLES, m_entitiesTotalInidicies[i], GL_UNSIGNED_INT, 0);
    }
}
