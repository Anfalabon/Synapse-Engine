#pragma once

#include <glad/glad.hpp>


#include <iostream>
#include <string.h>
#include <vector>

//for me this is much better than the second one which has more useless abstraction

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

     void readSources();
     [[nodiscard]] GLuint ProgramID(){return m_shaderProgramID;}
     void setup();
     void link();
     void setupSuccessLog();
     void remove();
     void removeProgram();
     void useProgram();

 private:

     //ID's of the shaders
     GLuint m_vertexShaderID;
     GLuint m_fragmentShaderID;

     GLuint m_shaderProgramID;

     ShaderFile m_vertexShader;
     ShaderFile m_fragmentShader;

 };














