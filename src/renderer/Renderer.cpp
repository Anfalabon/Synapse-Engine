#include "Renderer.hpp"
#include "../scene/Scene.hpp"
#include "../utils/RunParallel.hpp"
//#include "../multithreading/runParallel.hpp"

#include <glm/glm.hpp>

#include <future>
#include <thread>
#include <vector>



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


static void SetMatrix(GLuint shaderProgramID, const char *uniformMatrixName, glm::mat4 &model)
{
    GLuint modelLocation = glGetUniformLocation(shaderProgramID, uniformMatrixName);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}

//static void Transformation(glm::mat4 &model, )
//{
//    model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5));
//    model = glm::translate(model, glm::vec3(0.0f, (float)2.0f, 0.0f));
//}


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


//    scene->GetRenderableObject(0)->GetVA().Bind();
//    scene->GetRenderableObject(1)->GetVA().Bind();
//    scene->GetRenderableObject(2)->GetVA().Bind();

//    std::vector<glm::mat4> models;
//    models[0] = glm::mat4(1.0f);
//    models[1] = glm::mat4(1.0f);
//    models[2] = glm::mat4(1.0f);

//    scene->GetRenderableObject(2)->GetVA().Bind();
//    scene->GetRenderableObject(2)->GetShader().UseProgram();
//
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(1.0f, 1.0f, 0.0f));
//    SetMatrix(scene->GetRenderableObject(2)->GetShader().ProgramID(), "model", model);

    //glm::mat4 model = glm::mat4(1.0f);



    //GLuint *ptr = &scene->GetRenderableObject(0)->GetEB().GetTotalIndicies();

//    scene->GetRenderableObject(0)->GetVA().Bind();


    glm::vec3 translationVectors[3] = {
            glm::vec3(0.0f, 1.0f/100.0f, 0.0f),     //moves the Ligth source(first object upwards)
            glm::vec3(0.0f, 0.0f, 0.0f),    //moves the Ground(second object downwards)
            glm::vec3(0.0f, 0.0f, 0.0f)
    };

    float rotationAngles[3] = {
            0.0f,
            0.0f,
            1.0f
    };

    glm::vec3 rotationalVectors[3] = {
            glm::vec3(1.0, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
    };


//    model = scene->GetRenderableObject(0)->m_model;

    for(std::size_t i=0; i < scene->GetTotalSceneObjects(); ++i)
    {
        scene->GetRenderableObject(i)->GetVA().Bind();

//        float angle = 10.0f;
//        glm::mat4 model = glm::mat4(1.0f);

        scene->GetRenderableObject(i)->m_model = glm::rotate(scene->GetRenderableObject(i)->m_model, rotationAngles[i], glm::vec3(1.0f, 0.0f, 0.0f));
        scene->GetRenderableObject(i)->m_model = glm::translate(scene->GetRenderableObject(i)->m_model, translationVectors[i]);
        scene->GetRenderableObject(i)->GetShader().SendMatrix4ToGPU("model", scene->GetRenderableObject(i)->m_model);


        //render every object
        glDrawElements(GL_TRIANGLES, scene->GetRenderableObject(i)->GetEB().GetTotalIndicies(), GL_UNSIGNED_INT, 0);
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
