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
    :
     m_name(model.first.c_str()),
     m_VB(model.second._totalVerticies, model.second._verticiesData),
     m_EB(model.second._totalIndicies, model.second._indiciesData){}


//RenderableObject::RenderableObject(const std::pair<std::string, Synapse::Mesh> &model)
//{
//    m_name = model.first.c_str();
//    std::cout << "Going to load the first model mesh..." << '\n';
//    m_meshes.push_back(Mesh());
//    std::cout << "Finished loading the first model mesh..." << '\n';
//}




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

        m_meshes[i]._VA.SetVertexLayout(0, 3, 6);   //for Position
        m_meshes[i]._VA.SetVertexLayout(1, 3, 6);   //for Color

        m_meshes[i]._VA.Unbind();
        m_meshes[i]._VB.Unbind();
    }
}




void RenderableObject::LoadVertexObjects(unsigned short objectsInSingleVertex, bool addTexture)
{
    m_VA.Gen();
    m_VB.Gen();
    m_EB.Gen();

    m_VA.Bind();
    m_VB.Bind();
    m_EB.Bind();

    m_VA.SetVertexLayout(0, 3, objectsInSingleVertex);  //for Position
    m_VA.SetVertexLayout(1, 3, objectsInSingleVertex);  //for Color
    if(addTexture)
    {
        m_VA.EnableVertexAttribute(2, 2, objectsInSingleVertex);   //for Texture  //will have to choose others also 8 if we add texture
    }

    m_VA.Unbind();
    m_VB.Unbind();
}


void RenderableObject::LoadTexture()
{
    //unsigned int texture;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../vendor/imageLoader/groundTexture.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << '\n';
    }
    stbi_image_free(data);
}


void RenderableObject::Translate(const glm::vec3 &translationVec)
{
    m_model = glm::translate(m_model, translationVec);
}


void RenderableObject::Rotate(float angleToRotateDegrees, const glm::vec3 &rotationVec)
{
    m_model = glm::rotate(m_model, glm::radians(angleToRotateDegrees), rotationVec);
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

