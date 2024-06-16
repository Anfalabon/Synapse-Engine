#pragma once

#include <glad/glad.hpp>

#include <iostream>
#include <string.h>


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

     Shader() = default;
     Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
        :
       m_vertexShaderID(glCreateShader(GL_VERTEX_SHADER)),
       m_fragmentShaderID(glCreateShader(GL_FRAGMENT_SHADER)),
       m_shaderProgramID(glCreateProgram())
     {
         m_vertexShader.path = std::move(vertexShaderPath);
         m_fragmentShader.path = std::move(fragmentShaderPath);
     }

     //by now it's now defualt cause it may delete the program(which is kind of optional)
     ~Shader()
     {
         //glDeleteProgram(m_shaderProgramID);
     }

     void ReadSources();
     [[nodiscard]] GLuint ProgramID(){return m_shaderProgramID;}
     template<typename T> void SetupSuccessLog(T __STATUS__, GLuint shaderID);
     void Setup();
     void AttachAndLink();
     void UseProgram();
     void RemoveShaders();
     void RemoveProgram();

private:

     //ID's of the shaders
     GLuint m_vertexShaderID;
     GLuint m_fragmentShaderID;

     GLuint m_shaderProgramID;

     ShaderFile m_vertexShader;
     ShaderFile m_fragmentShader;

};




}














