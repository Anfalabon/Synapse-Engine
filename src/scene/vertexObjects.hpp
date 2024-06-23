#pragma once

#include <glad/glad.hpp>

#include <iostream>
#include <array>
#include <vector>



namespace Synapse
{

typedef struct Vertex
{
    GLfloat positions[3];
    GLfloat colors[3];

//    Vertex &operator[]()
//    {
//        return *this;
//    }



    inline friend std::ostream &operator<<(std::ostream &os, const struct Vertex &vertex);

}Vertex;



std::ostream &operator<<(std::ostream &os, const struct Vertex &vertex)
{
    os << vertex;
    return os;
}


struct VertexObjects
{
public:
    VertexObjects(GLuint verticiesSizeBytes, const void *verticiesData,
                  GLuint indiciesSizeBytes, const void *indiciesData) noexcept;
    ~VertexObjects();

    [[nodiscard]] inline GLuint &GetVAO(){return _VAO;}
    [[nodiscard]] inline GLuint &GetEBO(){return _EBO;}
    [[nodiscard]] inline GLuint &GetVBO(){return _VBO;}

private:
    GLuint _VBO;
    GLuint _VAO;
    GLuint _EBO;

    bool _elementBufferexist;

};


struct VertexBuffer
{
    VertexBuffer() = default;
    VertexBuffer(GLuint totalVerticies, Vertex *verticiesData)
    :     _totalVerticies(totalVerticies),
          _verticiesData(verticiesData){}

    ~VertexBuffer()
    {
        glDeleteBuffers(1, &_VBO);
        if(_verticiesData!=nullptr)
        {
            delete[] _verticiesData;
            //delete[] (Vertex*)_verticiesData;
        }
    }

    void SetVerticies(GLuint totalVerticies, Vertex *verticiesData)
    {
        _totalVerticies = totalVerticies;
        _verticiesData = std::move(verticiesData);
    }

    void Gen()
    {
        glGenBuffers(1, &_VBO);
    }

    void Bind()
    {
        //_verticiesData = &_vVerticiesData[0];
        unsigned long TARGET_BUFFER = 0x8892;   //GL_ARRAY_BUFFER
        glBindBuffer(TARGET_BUFFER, _VBO);
        glBufferData(TARGET_BUFFER, sizeof(Vertex)*_totalVerticies, _verticiesData, GL_DYNAMIC_DRAW);
    }

    void Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint &GetVBO()
    {
        return _VBO;
    }

    GLuint GetTotalVerticies()
    {
        return _totalVerticies;
    }

    Vertex *GetVerticiesData()
    {
        //return (Vertex*)_verticiesData;
        return _verticiesData;
    }

private:
    GLuint _VBO;
    GLuint _totalVerticies;
    Vertex *_verticiesData;

//    std::vector<Vertex> _vVerticiesData = {
//            //vertex positions      //colors
//            {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
//            {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 1.0f}},
//            {{0.5f,  -0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}},
//            {{0.5f,  -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
//            {{-0.5f, 0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
//            {{-0.5f, 0.5f,  -0.5f}, {1.0f, 1.0f, 1.0f}},
//            {{-0.5f, -0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}},
//            {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}
//    };
};



struct IndexBuffer
{
    IndexBuffer() = default;
    IndexBuffer(GLuint totalIndicies, GLuint *indiciesData)
    :    _totalIndicies(totalIndicies),
         _indiciesData(std::move(indiciesData)){}

    ~IndexBuffer()
    {
        glDeleteBuffers(1, &_EBO);
        if(_indiciesData!=nullptr)
        {
            delete[] _indiciesData;
            //delete[] (GLuint*)_indiciesData;
        }
    }

    void SetIndicies(GLuint totalIndicies, GLuint *indiciesData)
    {
        _totalIndicies = totalIndicies;
        _indiciesData = std::move(indiciesData);
    }

    void Gen()
    {
        glGenBuffers(1, &_EBO);
    }

    void Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*_totalIndicies, _indiciesData, GL_DYNAMIC_DRAW);
    }

    void Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLuint &GetEBO()
    {
        return _EBO;
    }

    GLuint GetTotalIndicies()
    {
        return _totalIndicies;
    }

    GLuint *GetIndiciesData()
    {
        //return (GLuint*)_indiciesData;
        return _indiciesData;
    }

private:
    GLuint _EBO;
    GLuint _totalIndicies;
    GLuint *_indiciesData;
};


struct VertexArray
{
    VertexArray() = default;
    ~VertexArray()
    {
        glDeleteVertexArrays(1, &_VAO);
    }

    void Gen()
    {
        glGenVertexArrays(1, &_VAO);
    }

    void Bind()
    {
        glBindVertexArray(_VAO);
    }

    void Unbind()
    {
        glBindVertexArray(0);
    }

    void EnableVertexAttribute(unsigned short vertexAttributeNo)
    {
        glVertexAttribPointer(vertexAttributeNo, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*vertexAttributeNo * sizeof(GLfloat)));
        glEnableVertexAttribArray(vertexAttributeNo);
    }

    GLuint &GetVAO()
    {
        return _VAO;
    }

private:
    GLuint _VAO;
};


typedef struct VertexBuffer VertexBuffer;
typedef struct IndexBuffer IndexBuffer;
typedef struct VertexArray VertexArray;



}

