#pragma once

#include <glad/glad.hpp>
#include <glm/glm.hpp>

#include "core/Macros.hpp"

#include <iostream>
#include <string.h>
#include <unordered_map>


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
     Shader(const Shader &) = default;  //Copy Constructor
     Shader &operator=(const Shader &) = default;   //Copy assignment operator

     Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
        :
       m_vertexShaderID(glCreateShader(GL_VERTEX_SHADER)),
       m_fragmentShaderID(glCreateShader(GL_FRAGMENT_SHADER)),
       m_shaderProgramID(glCreateProgram())
     {
         m_vertexShader.path = vertexShaderPath;
         m_fragmentShader.path = fragmentShaderPath;
     }

     //by now it's now defualt cause it may delete the program(which is kind of optional)
     ~Shader()
     {
         //glDeleteProgram(m_shaderProgramID);
     }

     template<typename T> void SetupSuccessLog(T __STATUS__, GLuint shaderID) const;
     void Compile();
     unsigned int Compile(unsigned int type, const char *shaderSource) const;
     void AttachAndLink() const;
     void UseProgram() const;
     void RemoveShaders() const;
     void RemoveProgram() const;


     __ALWAYS__INLINE__ unsigned int GetProgramID() const {return m_shaderProgramID;}
     __ALWAYS__INLINE__ std::string  GetVertexShaderFilePath() const {return m_vertexShader.path;}
     __ALWAYS__INLINE__ std::string  GetFragmentShaderFilePath() const {return m_fragmentShader.path;}

     __ALWAYS__INLINE__ void SetShader()
     {
         this->Compile();
         this->AttachAndLink();
         this->RemoveShaders();
     }


     void SetMatrix4vf(const char *uniformMatrixName, glm::mat4 &model);
     void SendMatrix4ToGPU(const char *uniformMatrixName, glm::mat4 &model);
     void SendVector3ToGPU(const char *uniformVectorName, glm::vec3 &vector);


private:


     unsigned int GetUniformLocation(const char *uniformName);

     //ID's of the shaders
     GLuint m_vertexShaderID;
     GLuint m_fragmentShaderID;

     GLuint m_shaderProgramID;

     ShaderFile m_vertexShader;
     ShaderFile m_fragmentShader;

     std::unordered_map<const char*, unsigned int> m_uniformLocationCacheMap;   //utilizing the cache by validating it.

};




}














