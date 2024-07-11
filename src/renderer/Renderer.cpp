#include "Renderer.hpp"
#include "scene/Scene.hpp"
#include "core/RunParallel.hpp"
#include "debug/LOG.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>


#include <iostream>
#include <vector>
#include <thread>
#include <filesystem>
#include <sys/stat.h>
#include <chrono>
#include <ctime>




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
//    for(std::size_t i=0; i<m_totalEntities; ++i)
//    {
//          glBindVertexArray(m_entitiesVAO[i]);
//          glDrawElements(GL_TRIANGLES, m_entitiesTotalIndicies[i], GL_UNSIGNED_INT, 0);
//    }
#endif
}



void SceneRenderer::RenderScenePartially(Scene *scene, std::vector<Shader> &sceneShaders, std::size_t first, std::size_t last)
{
    for(std::size_t i=first; i<last; ++i)
    {
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, scene->GetRenderableObject(i)->GetMesh(0)._texture.GetTextureID());
        scene->GetRenderableObject(i)->GetMesh(0)._VA.Bind();

        sceneShaders[0].SendMatrix4ToGPU("model", scene->GetRenderableObject(i)->m_model);
        sceneShaders[0].SendVector3ToGPU("position", scene->GetRenderableObject(i)->m_position);

        //render every object
        glDrawElements(GL_TRIANGLES, scene->GetRenderableObject(i)->GetTotalIndiciesOfMesh(0), GL_UNSIGNED_INT, 0);
    }
}





//track the file creation time and last file modification time.
//if the last file modification time > creation time then file was modified.
//assign the last modification time to current time(the current time was was checked).

//again if the current modification time > last modification time then file was modified.


bool SceneRenderer::WasShaderFileModified(const std::string &filePathStr)
{
    //const char *filePath = filePathStr.c_str();
    struct stat fileInfo;
    std::time_t currentLastModificationTime;

    if(struct stat fileInfo; stat(filePathStr.c_str(), &fileInfo) == 0)
    {
        currentLastModificationTime = fileInfo.st_mtime;
        if(fileInfo.st_mtime > lastModificationTime)
        {
            lastModificationTime = fileInfo.st_mtime;
            return true;
        }
    }

    if(currentLastModificationTime > lastModificationTime)
    {
        lastModificationTime = currentLastModificationTime;
        return true;
    }
    else
    {
        return false;
    }

}



void SceneRenderer::Render(Scene *scene, Shader *sceneShaders)
{



//    m_sceneShaders[0].SendMatrix4ToGPU("model", scene->GetRenderableObject(0)->m_model);
//    m_sceneShaders[0].SendMatrix4ToGPU("model", scene->GetRenderableObject(1)->m_model);
//    m_sceneShaders[0].SendMatrix4ToGPU("model", scene->GetRenderableObject(2)->m_model);



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





    //unsigned int *ptr = &scene->GetRenderableObject(0)->GetTotalIndiciesOfMesh(0);
    //*(ptr + i*sizeof(Scene))


#if 1


    if(m_fileWatcher.WasFileModified("../src/renderer/shader/GLSL/vertexShader1.vert") ||
       m_fileWatcher.WasFileModified("../src/renderer/shader/GLSL/fragmentShader1.frag"))
    {
        this->SetShader();
        m_sceneShaders[0].UseProgram();
    }

    //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

    //#pragma omp parallel for
    for(std::size_t i=0; i < scene->GetTotalSceneObjects(); ++i)
    {
        //glBindTexture(GL_TEXTURE_2D, scene->GetRenderableObject(i)->GetTextureID());
        //scene->GetRenderableObject(i)->GetVA().Bind();

        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, scene->GetRenderableObject(i)->GetMesh(0)._texture.GetTextureID());
        scene->GetRenderableObject(i)->GetMesh(0)._VA.Bind();

        m_sceneShaders[0].SendMatrix4ToGPU("model", scene->GetRenderableObject(i)->m_model);
        m_sceneShaders[0].SendVector3ToGPU("position", scene->GetRenderableObject(i)->m_position);

        //render every object
        glDrawElements(GL_TRIANGLES, scene->GetRenderableObject(i)->GetTotalIndiciesOfMesh(0), GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, scene->GetRenderableObject(i)->GetTotalIndicies(), GL_UNSIGNED_INT, 0);

    }


#endif


//    std::thread sceneRendererThread1(RenderScenePartially, scene, m_sceneShaders, 0, scene->GetTotalSceneObjects()/2);
//    std::thread sceneRendererThread2(RenderScenePartially, scene, m_sceneShaders, scene->GetTotalSceneObjects()/2, scene->GetTotalSceneObjects());
//
//
//    sceneRendererThread1.join();
//    sceneRendererThread2.join();





#endif

    std::cout << "Finised rendering current scene!" << '\n';

}





#endif




void ImageRenderer::Render()
{
    //render image by pixel by pixel
}





}
