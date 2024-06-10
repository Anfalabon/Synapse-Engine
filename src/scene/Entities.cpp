

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
     m_verticies(std::move(verticies)),
     m_indicies(std::move(indicies)),
     m_totalVerticies(totalVerticies),
     m_totalIndicies(totalIndicies),
     m_verticiesSizeBytes(sizeof(Vertex)*totalVerticies),
     m_indiciesSizeBytes(sizeof(GLuint)*totalIndicies),
     m_shader(vertexShaderSourcePath, fragmentShaderSourcePath),
     m_VO(m_verticiesSizeBytes, m_verticies, m_indiciesSizeBytes, m_indicies){}



void RenderableObject::LoadShader()
{
    m_shader.Setup();
    m_shader.AttachAndLink();
}


void RenderableObject::PrintVerticiesData()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    for (std::size_t i = 0; i < m_totalVerticies; ++i)
    {
        std::cout << m_verticies[i] << '\n';
    }
}


void RenderableObject::PrintIndiciesData()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    for (std::size_t i = 0; i < m_totalIndicies; ++i)
    {
        std::cout << m_indicies[i] << '\n';
    }
}



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
    GLuint modelLocation = glGetUniformLocation(m_shader.ProgramID(), "model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_Transform.m_model));
}

//first update and then render
void RenderableObject::Render()
{
    //glDrawArrays(GL_TRIANGLES, 0, 36)
    glBindVertexArray(m_VO.GetVAO());
    glDrawElements(GL_TRIANGLES, m_totalIndicies, GL_UNSIGNED_INT, 0);
}



RenderableObject::~RenderableObject()
{
    //in constructor initializer list m_verticies and m_indicies was assigned to verticiesArr and indiciesArr
    //so now both owns the verticies and indicies data
    //we will delete the verticies and indicies data from the Entity destructor
    //it will prevent us from doing manual deletion in InitializeEngine.cpp where the entities are deleted explicitly at the end of the program
    if(m_verticies!=nullptr)
    {
        delete[] m_verticies;
    }
    if(m_indicies!=nullptr)
    {
        delete[] m_indicies;
    }
}



}

