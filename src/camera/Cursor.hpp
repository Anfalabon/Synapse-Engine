#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


namespace Synapse
{

//will make it a struct called "Calculate and the mouseInput will be inside Calculate::Cursor."
namespace Cursor
{

inline float m_lastX = 1920.0f / 2.0f;
inline float m_lastY = 1080.0f / 2.0f;
inline float m_yaw = -90.0f;
inline float m_pitch = 0.0f;
inline const float m_sensitivity = 0.1f;

inline bool m_firstMouse = true;
inline bool m_isMouseMoving = false;
inline glm::vec3 m_frontVector = glm::vec3(0.0f, 0.0f, 0.0f);


//calculate the direction where the mouse/cursor is pointing to
//this calculates the vector where the camera will look at after certain changes in mouse input
static void CalculateDirectionVector()
{
    glm::vec3 frontVector;
    frontVector.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    frontVector.y = glm::sin(glm::radians(m_pitch));
    frontVector.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    m_frontVector = glm::normalize(frontVector);
}


static void mouseInput(GLFWwindow *window, double xpos, double ypos)
{
    m_isMouseMoving = true;
    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;

        m_firstMouse = false;
    }

    float Xoffset = xpos - m_lastX;
    float Yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;

    //calculate the offset
    Xoffset = Xoffset * m_sensitivity;
    Yoffset = Yoffset * m_sensitivity;

    //calculate yaw and pitch
    m_yaw = m_yaw + Xoffset;
    m_pitch = m_pitch + Yoffset;
    //set the moving speed constant of the camera when't it's pointing at 90 degree or right angle
    //cause camera speed is slower at 90 or -90 degree pitch //but this is still not that good cause it only works for some degrees
    if (m_pitch > 89.0f)
    {
        m_pitch = 89.0f;
    }
    else if (m_pitch < -89.0f)
    {
        m_pitch = -89.0f;
    }

    CalculateDirectionVector();

}

}



}


