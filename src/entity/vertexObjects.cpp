

#include "vertexObjects.hpp"



VertexObjects::VertexObjects(GLuint verticiesSizeBytes, const void *verticiesData,
                             GLuint indiciesSizeBytes, const void *indiciesData) noexcept
{
    if(verticiesSizeBytes <= 0 || verticiesData == nullptr ||
       indiciesSizeBytes <= 0 || indiciesData == nullptr)
    {
        return;
    }

    //GLuint VBO;
    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, verticiesSizeBytes, verticiesData, GL_STATIC_DRAW);

    //we strictly have to gen, bind, set offset and enable the vertex array object(VAO) right after vertex buffer object(VBO)
    //GLuint VAO;
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    //for the position vertex attribute (layout (location = 0))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    //for the color vertex attribute (layout (location = 1))
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //GLuint EBO;
    glGenBuffers(1, &_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesSizeBytes, indiciesData, GL_STATIC_DRAW);

}

VertexObjects::~VertexObjects()
{
    //unbind the vertex buffer object, element buffer object and vertex array object
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //delete the vertex arrays, vertex buffers and element buffers
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
}
