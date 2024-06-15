#include "Renderer.hpp"
#include "../scene/Scene.hpp"
#include "../utils/RunParallel.hpp"
//#include "../multithreading/runParallel.hpp"

#include <future>
#include <thread>




//#define __MULTITHREADING__RENDERER__



namespace Synapse
{
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

void Renderer::SetBackGround(float r, float g, float b, float w)
{
    glClearColor(r, g, b, w);
}

void Renderer::UseZbuffer()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




#if defined(__UTILIZE__STANDARDCXX__THREADING___)
//this was for multithreading using std::thread or std::future+std::async
void EntityRenderer::renderEntitiesPartially(std::size_t start, std::size_t end)
{
    for(std::size_t i=start; i<end; ++i)
    {
        glBindVertexArray(m_entitiesVAO[i]);
        glDrawElements(GL_TRIANGLES, m_entitiesTotalIndicies[i], GL_UNSIGNED_INT, 0);
    }
}
#else

//rendering like this is much faster as we are storing the entities infos' in a contiguous memory.
//with this CPU's L1 cahce memroy get's more chance to deal with faster accessing
void SceneRenderer::Render()
{
#if defined(__MULTITHREADING__RENDERER__)

    //this somehow causes rendering only the first entitty in the 'm_entities' contianer in 'Engine' class.
    //it's probably because of 'race condition'.
    //will fix it.
    unsigned short threadsToUtilize = 0x4;
    Threading::S_pragma_omp_parallel_loop<void, std::size_t>(0, m_totalEntities, threadsToUtilize,
    [this](auto i)->void
    {
          //#pragma omp critical
          glBindVertexArray(m_entitiesVAO[i]);
          glDrawElements(GL_TRIANGLES, m_entitiesTotalIndicies[i], GL_UNSIGNED_INT, 0);
    });
#else
    for(std::size_t i=0; i<m_totalEntities; ++i)
    {
          glBindVertexArray(m_entitiesVAO[i]);
          glDrawElements(GL_TRIANGLES, m_entitiesTotalIndicies[i], GL_UNSIGNED_INT, 0);
    }
#endif
}




void SceneRenderer::Render(Scene *scene)
{

#if defined(__MULTITHREADING__RENDERER__)
    auto ThreadsToUtilize = [=]()->unsigned short
    {
        //there maybe an threshold in the number of scene objects for which a the threads to utilize for rendering would be set
        //right now the threshold is 1000
        return (scene->GetTotalSceneObjects() > 1000) ? 0x4 : 0x1;
    };
    //using this causes weird rendering(it only renders the first renderable object in the scene)
    unsigned short threadsToUtilize = 0x3;
    Threading::S_pragma_omp_parallel_loop<void, std::size_t>(0, scene->GetTotalSceneObjects(), ThreadsToUtilize(),
    [&scene](auto i)->void
    {
         #pragma omp critical
         glBindVertexArray(scene->GetRenderableObject(i)->GetVertexObjects().GetVAO());
         glDrawElements(GL_TRIANGLES, scene->GetRenderableObject(i)->TotalIndicies(), GL_UNSIGNED_INT, 0);
    });
#else
    for(std::size_t i=0; i < scene->GetTotalSceneObjects(); ++i)
    {
        glBindVertexArray(scene->GetRenderableObject(i)->GetVertexObjects().GetVAO());
        glDrawElements(GL_TRIANGLES, scene->GetRenderableObject(i)->TotalIndicies(), GL_UNSIGNED_INT, 0);
    }
#endif

    std::cout << "Finised rendering current scene!" << '\n';

}





#endif









void ImageRenderer::Render()
{
    //render image by pixel by pixel
}

}
