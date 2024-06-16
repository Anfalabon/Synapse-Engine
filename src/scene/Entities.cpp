

#include "Entities.hpp"


#ifdef __stdcxx__
    #include <random>
#else
    #include <cstdlib>
#endif


namespace Synapse
{


template<typename T>
static std::size_t GetSize(T *arr)
{
    std::size_t i=0;
    while(!arr[++i])
        ;;
    return i;
}



RenderableObject::RenderableObject(const char *name,
               Vertex *verticies, GLuint totalVerticies,
               GLuint *indicies, GLuint totalIndicies,
               const std::string &vertexShaderSourcePath,
               const std::string &fragmentShaderSourcePath) noexcept
    :
     m_name(name),
     m_ID(rand()%INT_MAX),  //i know it's bad to use but still...
     m_shader(vertexShaderSourcePath, fragmentShaderSourcePath),
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

void RenderableObject::SetShaderSources(const std::string &vertexShaderSourcePath, const std::string &fragmentShaderSourcePath)
{
    m_shader = Shader(vertexShaderSourcePath, fragmentShaderSourcePath);
}

void RenderableObject::LoadShader()
{
    //m_shader = Shader(vertexShaderSourcePath, fragmentShaderSourcePath);
    m_shader.Compile();
    m_shader.AttachAndLink();
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


//these shouldn't be inside 'RenderableObjects' class

void RenderableObject::Translate(glm::vec3 translationVec)
{
    m_Transform.m_model = glm::translate(m_Transform.m_model, translationVec);
    m_Transform.ModelLocation(m_shader.ProgramID());
}


void RenderableObject::Rotate(float angleToRotateDegrees, glm::vec3 rotationVec)
{
    m_Transform.m_model = glm::rotate(m_Transform.m_model, glm::radians(angleToRotateDegrees), rotationVec);
    m_Transform.ModelLocation(m_shader.ProgramID());
}


void RenderableObject::Scale(glm::vec3 scaleVec)
{
    m_Transform.m_model = glm::scale(m_Transform.m_model, scaleVec);
}


void RenderableObject::Update()
{
    m_shader.UseProgram();
    //m_Transform.ModelLocation(m_shader.ProgramID());
    m_shader.SendMatrix4ToGPU("model", m_model);    //this is not necessary to do everytime if entities model matrix don't change everytime

//    GLuint modelLocation = glGetUniformLocation(m_shader.ProgramID(), "model");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_Transform.m_model));
}


RenderableObject::~RenderableObject()
{
    //in constructor initializer list m_verticies and m_indicies was assigned to verticiesArr and indiciesArr
    //so now both owns the verticies and indicies data
    //we will delete the verticies and indicies data from the Entity destructor
    //it will prevent us from doing manual deletion in InitializeEngine.cpp where the entities are deleted explicitly at the end of the program
}



}

