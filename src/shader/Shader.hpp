#pragma once

#include <glad/glad.hpp>


#include <iostream>
#include <string.h>
#include <vector>


namespace Synapse
{

class Shader
{
public:
    typedef struct ShaderFile
    {
        std::string source;
        std::string path;
    }ShaderFile;

     Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
         :
           m_vertexShaderID(glCreateShader(GL_VERTEX_SHADER)),
           m_fragmentShaderID(glCreateShader(GL_FRAGMENT_SHADER)),
           m_shaderProgramID(glCreateProgram())
           {
               m_vertexShader.path = vertexShaderPath;
               m_fragmentShader.path = fragmentShaderPath;
           }

     ~Shader()
     {
         glDeleteShader(m_vertexShaderID);
         glDeleteShader(m_fragmentShaderID);

         glDeleteProgram(m_shaderProgramID);
     }

     void ReadSources();
     [[nodiscard]] GLuint ProgramID(){return m_shaderProgramID;}
     void Setup();
     void Link();
     void SetupSuccessLog();
     void Remove();
     void RemoveProgram();
     void UseProgram();

private:

     //ID's of the shaders
     GLuint m_vertexShaderID;
     GLuint m_fragmentShaderID;

     GLuint m_shaderProgramID;

     ShaderFile m_vertexShader;
     ShaderFile m_fragmentShader;

};




}














