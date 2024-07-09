#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


namespace Synapse
{



struct CursorData
{
    bool  m_movedForTheFirstTime;
    float m_lastX;
    float m_lastY;
    float m_yaw;
    float m_pitch;
    const float m_sensitivity;
    bool  m_isMoving;
    glm::vec3 m_frontVector;
};



//may make it a struct called "Cursor" and the mouseInput will be inside Calculate::Cursor
namespace Cursor
{

inline float g_lastX = 1920.0f / 2.0f;
inline float g_lastY = 1080.0f / 2.0f;
inline float g_yaw = -90.0f;
inline float g_pitch = 0.0f;
inline const float g_sensitivity = 0.1f;

inline bool g_movedMouseForTheFirstTime = true;
inline bool g_isMouseMoving = false;
inline glm::vec3 g_frontVector = glm::vec3(0.0f, 0.0f, 0.0f);

//calculate the direction where the mouse/cursor is pointing to
//this calculates the vector where the camera will look at after certain changes in mouse input
static void CalculateFrontVector() //this is equavalent to calculating the cameraFront vector
{
    glm::vec3 frontVector;  //using this is maybe waste of memory when everytime mouse is moved
    frontVector.x = glm::cos(glm::radians(g_yaw)) * glm::cos(glm::radians(g_pitch));
    frontVector.y = glm::sin(glm::radians(g_pitch));
    frontVector.z = glm::sin(glm::radians(g_yaw)) * glm::cos(glm::radians(g_pitch));
    g_frontVector = glm::normalize(frontVector);
}


static void mouseInput(GLFWwindow *window, double xpos, double ypos)
{

    //MouseEvents cursor;

    if (g_movedMouseForTheFirstTime)
    {
        g_lastX = xpos;
        g_lastY = ypos;

        g_movedMouseForTheFirstTime = false;
    }

    float Xoffset = xpos - g_lastX;
    float Yoffset = g_lastY - ypos;

    g_lastX = xpos;
    g_lastY = ypos;

    //calculate the offset
    Xoffset = Xoffset * g_sensitivity;
    Yoffset = Yoffset * g_sensitivity;

    //calculate yaw and pitch
    g_yaw = g_yaw + Xoffset;
    g_pitch = g_pitch + Yoffset;
    //set the moving speed constant of the camera when't it's pointing at 90 degree or right angle
    //cause camera speed is slower at 90 or -90 degree pitch //but this is still not that good cause it only works for some degrees
    if (g_pitch > 89.0f)
    {
        g_pitch = 89.0f;
    }
    else if (g_pitch < -89.0f)
    {
        g_pitch = -89.0f;
    }

    CalculateFrontVector();

}



static void MultipleMouseInput(GLFWwindow *window, double xpos, double ypos)
{
    //m_cameras[m_currentCameraIndex]->cursor.g_movedMouseForTheFirstTime
    if (g_movedMouseForTheFirstTime)
    {
        g_lastX = xpos;
        g_lastY = ypos;

        g_movedMouseForTheFirstTime = false;
    }

    float Xoffset = xpos - g_lastX;
    float Yoffset = g_lastY - ypos;

    g_lastX = xpos;
    g_lastY = ypos;

    //calculate the offset
    Xoffset = Xoffset * g_sensitivity;
    Yoffset = Yoffset * g_sensitivity;

    //calculate yaw and pitch
    g_yaw = g_yaw + Xoffset;
    g_pitch = g_pitch + Yoffset;
    //set the moving speed constant of the camera when't it's pointing at 90 degree or right angle
    //cause camera speed is slower at 90 or -90 degree pitch //but this is still not that good cause it only works for some degrees
    if (g_pitch > 89.0f)
    {
        g_pitch = 89.0f;
    }
    else if (g_pitch < -89.0f)
    {
        g_pitch = -89.0f;
    }

    CalculateFrontVector();

    //m_cameras[m_currentCameraIndex]->CalculateFrontVector();

}




}



}


