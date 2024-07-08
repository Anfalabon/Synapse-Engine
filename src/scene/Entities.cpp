#include "Entities.hpp"
#include "../utils/MemoryManager.hpp"

#include <stb_image.h>

#ifdef __stdcxx__
    #include <random>
#else
    #include <cstdlib>
#endif


namespace Synapse
{


RenderableObject::RenderableObject(const std::pair<std::string, Synapse::Mesh> &model)
{
    std::cout << "Constructing an RenderableObject..." << '\n';
    m_name = model.first.c_str();
    std::cout << "Is mesh loading going to crash..." << '\n';
    m_meshes.push_back(model.second);
    std::cout << "Loaded mesh successfully!" << '\n';
}




void RenderableObject::LoadMeshes()
{
    for(std::size_t i=0; i<m_meshes.size(); ++i)
    {
        m_meshes[i]._VA.Gen();
        m_meshes[i]._VB.Gen();
        m_meshes[i]._EB.Gen();

        m_meshes[i]._VA.Bind();
        m_meshes[i]._VB.Bind();
        m_meshes[i]._EB.Bind();

        m_meshes[i]._VA.SetVertexLayout(0, 3, 8);   //for Position
        m_meshes[i]._VA.SetVertexLayout(1, 3, 8);   //for Color
        m_meshes[i]._VA.SetVertexLayout(2, 2, 8);   //for Texture

        m_meshes[i]._VA.Unbind();
        m_meshes[i]._VB.Unbind();

        //m_meshes[i]._texture.Load();
    }

    for(std::size_t i=0; i<m_meshes.size(); ++i)
    {
        m_meshes[i]._texture.Load();
    }

}


void RenderableObject::Translate(const glm::vec3 &translationVec)
{
    m_model = glm::translate(m_model, translationVec);
}


void RenderableObject::Rotate(float angleToRotateDegrees, const glm::vec3 &rotationVec)
{
    m_model = glm::rotate(m_model, glm::radians(angleToRotateDegrees), rotationVec);
}


static void RotateAroundTwoAxis(float &firstAxisPos, float &secondAxisPos, float m_theta)
{
    float tempZ = firstAxisPos;
    firstAxisPos = glm::cos(m_theta)*firstAxisPos - glm::sin(m_theta)*secondAxisPos;
    secondAxisPos = glm::sin(m_theta)*tempZ + glm::cos(m_theta)*secondAxisPos;
}


void RenderableObject::Rotate(float angleToRotateDegrees, bool x, bool y, bool z)
{
    //float m_theta = glm::radians(angleToRotateDegrees);

    if(x && y)
        RotateAroundTwoAxis(m_position.x, m_position.y, glm::radians(angleToRotateDegrees));
    if(x && z)
        RotateAroundTwoAxis(m_position.x, m_position.z, glm::radians(angleToRotateDegrees));
    if(y && z)
        RotateAroundTwoAxis(m_position.y, m_position.z, glm::radians(angleToRotateDegrees));


}


void RenderableObject::Scale(const glm::vec3 &scaleVec)
{
    m_model = glm::scale(m_model, scaleVec);
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

