#pragma once

#include <stb_image.h>

#include "../debug/LOG.hpp"

#include <iostream>
#include <memory.h>

namespace Synapse
{

class Texture
{
public:
    Texture() = default;
    Texture(const char* filePath)
    : m_filePath(filePath)
    {
        std::cout << "Is constructing texture?" << '\n';
        m_loaded = false;
    };

    Texture(const Texture &otherTexture, bool x)    //this bool x is for memory error(Segmentation Fault)
    {
        DEBUG("Running Copy Constructor of Texture...");
        std::cin.get();

        m_width = otherTexture.m_width;
        m_height = otherTexture.m_height;
        m_nrChannels = otherTexture.m_nrChannels;

        memcpy(m_imageData, otherTexture.m_imageData, sizeof(unsigned char));
        if(m_imageData != nullptr)
        {
            m_loaded = true;
        }
    }

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

    bool m_loaded = false;

    unsigned char *m_imageData = nullptr;
    int m_width;
    int m_height;
    int m_nrChannels;
private:
    unsigned int m_textureID;
    const char *m_filePath = nullptr;   //relative to the build directory(where the Makefile is kept)
};


}