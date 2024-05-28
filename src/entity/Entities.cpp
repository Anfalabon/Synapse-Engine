

#include "Entities.hpp"



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


Entity::Entity(Vertex *verticies, GLuint totalVerticies,
               GLuint *indicies, GLuint totalIndicies,
               const std::string &vertexShaderSourcePath,
               const std::string &fragmentShaderSourcePath) noexcept
    :
     m_verticies(std::move(verticies)),
     m_indicies(std::move(indicies)),
     m_totalVerticies(totalVerticies),
     m_totalIndicies(totalIndicies),
     m_verticiesSizeBytes(sizeof(Vertex)*totalVerticies),
     m_indiciesSizeBytes(sizeof(GLuint)*totalIndicies),
     m_shader(vertexShaderSourcePath, fragmentShaderSourcePath),
     m_VO(m_verticiesSizeBytes, m_verticies, m_indiciesSizeBytes, m_indicies){}





void Entity::LoadShader()
{
    m_shader.Setup();
    m_shader.Link();
}


void Entity::PrintVerticiesData()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    for (std::size_t i = 0; i < m_totalVerticies; ++i)
    {
        std::cout << m_verticies[i] << '\n';
    }
}


void Entity::PrintIndiciesData()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    for (std::size_t i = 0; i < m_totalIndicies; ++i)
    {
        std::cout << m_indicies[i] << '\n';
    }
}



void Entity::Translate(glm::vec3 translationVec)
{
    m_coordinateTransform.m_model = glm::translate(m_coordinateTransform.m_model, translationVec);
    m_coordinateTransform.ModelLocation(m_shader.ProgramID());
}


void Entity::Rotate(float angleToRotateDegrees, glm::vec3 rotationVec)
{
    m_coordinateTransform.m_model = glm::rotate(m_coordinateTransform.m_model, glm::radians(angleToRotateDegrees), rotationVec);
    m_coordinateTransform.ModelLocation(m_shader.ProgramID());
}


void Entity::Scale()
{
    //scale the entity by parameter amount
}


void Entity::Render()
{
    //glDrawArrays(GL_TRIANGLES, 0, 36)
    glBindVertexArray(m_VO.GetVAO());
    glDrawElements(GL_TRIANGLES, m_totalIndicies, GL_UNSIGNED_INT, 0);
}



void Entity::Update()
{
    m_shader.UseProgram();
    m_coordinateTransform.ModelLocation(m_shader.ProgramID());
}


Entity::~Entity()
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

