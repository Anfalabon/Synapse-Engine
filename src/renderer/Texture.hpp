#pragma once

#include <stb_image.h>

namespace Synapse
{

class Texture
{
public:
    Texture() = default;
    Texture(const char* filePath)
    : m_filePath(filePath){};
    ~Texture() = default;

    void Gen();
    void Bind();
    void SetWrappingParameters();
    void SetFilteringParameters();
    void FlipVertically();
    void LoadImage();
    void CreateTextureAndGenerateMipMap();
    void Free();

    [[nodiscard]] inline unsigned int GetTextureID(){return m_textureID;}

    void Load();

private:
    unsigned char *m_imageData = nullptr;
    int m_width;
    int m_height;
    int m_nrChannels;
    unsigned int m_textureID;
    const char *m_filePath = nullptr;   //relative to the build directory(where the Makefile is kept)
};


}