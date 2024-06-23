

#include "Entities.hpp"
#include "../utils/MemoryManager.hpp"


#ifdef __stdcxx__
    #include <random>
#else
    #include <cstdlib>
#endif


namespace Synapse
{


RenderableObject::RenderableObject(const char *name,
               Vertex *verticies, GLuint totalVerticies,
               GLuint *indicies, GLuint totalIndicies) noexcept
    :
     m_name(name),
     m_ID(rand()%INT_MAX),  //i know it's bad to use but still...
     m_VB(totalVerticies, std::move(verticies)),
     m_EB(totalIndicies, std::move(indicies)){}


void RenderableObject::SetName(const char *name)
{
    if(name!=nullptr)
    {
        m_name = std::move(name);
    }
}

void RenderableObject::SetVerticies(GLuint totalVerticies, Vertex *verticies)
{
    //m_VB = struct VertexBuffer(totalVerticies, std::move(verticies));
    m_VB.SetVerticies(totalVerticies, std::move(verticies));
}

void RenderableObject::SetIndicies(GLuint totalIndicies, GLuint *indicies)
{
    //m_EB = struct IndexBuffer(totalIndicies, std::move(indicies));
    m_EB.SetIndicies(totalIndicies, std::move(indicies));
}


void RenderableObject::LoadVertexObjects()
{
    m_VA.Gen();
    m_VB.Gen();
    m_EB.Gen();

    m_VA.Bind();
    m_VB.Bind();
    m_EB.Bind();

    m_VA.EnableVertexAttribute(0);
    m_VA.EnableVertexAttribute(1);

    m_VA.Unbind();
    m_VB.Unbind();
}




void RenderableObject::Update()
{
    //m_shader.UseProgram();
    //m_shader.SendMatrix4ToGPU("model", m_model);    //this is not necessary to do everytime if entities model matrix don't change everytime
}


RenderableObject::~RenderableObject()
{
    //in constructor initializer list m_verticies and m_indicies was assigned to verticiesArr and indiciesArr
    //so now both owns the verticies and indicies data
    //we will delete the verticies and indicies data from the Entity destructor
    //it will prevent us from doing manual deletion in InitializeEngine.cpp where the entities are deleted explicitly at the end of the program
}



}

