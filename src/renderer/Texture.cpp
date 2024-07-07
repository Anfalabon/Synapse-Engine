#include "Texture.hpp"

#include <glad/glad.hpp>

#include <iostream>
#include <fstream>
#include <string.h>


namespace Synapse
{

void Texture::Gen()
{
    glGenTextures(1, &m_textureID);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::SetWrappingParameters()
{
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::SetFilteringParameters()
{
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void Texture::FlipVertically()
{
    stbi_set_flip_vertically_on_load(true);
}


void Texture::LoadImage()
{
    m_imageData = stbi_load(m_filePath, &m_width, &m_height, &m_nrChannels, 0);
}

void Texture::CreateTextureAndGenerateMipMap()
{
    if (m_imageData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << '\n';
    }
}

void Texture::Free()
{
    stbi_image_free(m_imageData);
}




void Texture::Load()
{
    //unsigned int texture;
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //stbi_set_flip_vertically_on_load(true);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    if(!m_loaded)
    {
        m_imageData = stbi_load(m_filePath, &m_width, &m_height, &m_nrChannels, 0);
        std::cout << "File path: "<< m_filePath << '\n';
    }

    if(m_imageData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << '\n';
    }

    //don't free the image buffer for later use
    //stbi_image_free(m_imageData);
}


}