#include "Texture.hpp"
#include "core/Macros.hpp"

#include <glad/glad.hpp>
#include <stb_image.h>


#include <fstream>
#include <string.h>


namespace Synapse
{


extern "C"{

#if defined(MSVC)
    __declspec() STBIDEF stbi_uc *stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
    __declspec() STBIDEF void     stbi_image_free(void *retval_from_stbi_load);
    __declspec() STBIDEF void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip);
#elif defined(__linux__) || defined(__unix__)
    __declspecUnix() STBIDEF stbi_uc *stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
    __declspecUnix() STBIDEF void     stbi_image_free(void *retval_from_stbi_load);
    __declspecUnix() STBIDEF void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip);
#elif defined(MAC)

#endif

}



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