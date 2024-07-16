#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>


namespace Synapse
{

//for now it's only for perspective projection
struct ProjectionData
{
    float m_fovDegrees;
    float m_aspectRatioY;
    float m_zNear;
    float m_zFar;
    float m_f;
};



class Projection
{
public:

    Projection() = default;
    ~Projection() = default;

    //virtual glm::mat4 SetProjection(){}

    static glm::mat4 Perspective(const struct ProjectionData &projectionData);
    static glm::mat4 Perspective(const float fovDegrees, const float aspectRatioY, const float zNear, const float zFar);
    static glm::mat4 Orthographic(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar);

protected:

    glm::mat4 m_projection = glm::mat4(1.0f);

    float m_zNear;
    float m_zFar;
};



class Perspective : public Projection
{
public:

private:

    float m_fovDegrees;
    float m_aspectRatioY;
    float m_f;
};



class Orthographic : public Projection
{
public:

private:

    float m_right;
    float m_left;
    float m_top;
    float m_bottom;
};


}

