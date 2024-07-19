#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

namespace Synapse
{


namespace Cursor
{



//will make it 'struct CursorData'
struct CursorData
{
    CursorData()                = default;
    ~CursorData()               = default;

    float m_lastX               = 1920.0f / 2.0f;
    float m_lastY               = 1080.0f / 2.0f;
    float m_yaw                 = -90.0f;
    float m_pitch               = 0.0f;
    const float m_sensitivity   = 0.1f;

    bool m_movedForTheFirstTime = true;
    //bool m_isMouseMoving        = false;
};



//struct Mouse
//{
//    inline std::vector<struct CursorData> g_cursorsData;
//    inline std::size_t g_cameraIndex;
//};


//definately using global variables are bad in this case where other good alternatives can be used instead
//Will remove these global variables and work with a safer one
inline std::vector<struct CursorData> g_cursorsData;
inline std::size_t g_cameraIndex;





static void mouseInput(GLFWwindow *window, double xpos, double ypos)
{

    std::cout << "Current Camera Index: " << g_cameraIndex << '\n';
    //std::cin.get();


    //MouseEvents cursor;

    if (g_cursorsData[g_cameraIndex].m_movedForTheFirstTime)
    {
        g_cursorsData[g_cameraIndex].m_lastX = xpos;
        g_cursorsData[g_cameraIndex].m_lastY = ypos;

        g_cursorsData[g_cameraIndex].m_movedForTheFirstTime = false;
    }

    float Xoffset = xpos - g_cursorsData[g_cameraIndex].m_lastX;
    float Yoffset = g_cursorsData[g_cameraIndex].m_lastY - ypos;

    g_cursorsData[g_cameraIndex].m_lastX = xpos;
    g_cursorsData[g_cameraIndex].m_lastY = ypos;

    //calculate the offset
    Xoffset *= g_cursorsData[g_cameraIndex].m_sensitivity;
    Yoffset *= g_cursorsData[g_cameraIndex].m_sensitivity;

    //calculate yaw and pitch
    g_cursorsData[g_cameraIndex].m_yaw += Xoffset;    //Mouse::g_cursorsData[Mouse::g_cameraIndex].m_yaw
    g_cursorsData[g_cameraIndex].m_pitch += Yoffset;  //Mouse::g_cursorsData[Mouse::g_cameraIndex].m_pitch


    //set the moving speed constant of the camera when't it's pointing at 90 degree or right angle
    //cause camera speed is slower at 90 or -90 degree pitch //but this is still not that good cause it only works for some degrees
    if (g_cursorsData[g_cameraIndex].m_pitch > 89.0f)
    {
        g_cursorsData[g_cameraIndex].m_pitch = 89.0f;
    }
    else if (g_cursorsData[g_cameraIndex].m_pitch < -89.0f)
    {
        g_cursorsData[g_cameraIndex].m_pitch = -89.0f;
    }

//    glm::vec3 frontVector;  //using this is maybe waste of memory when everytime mouse is moved
//    frontVector.x = glm::cos(glm::radians(g_cursorsData[g_cameraIndex].m_yaw)) * glm::cos(glm::radians(g_cursorsData[g_cameraIndex].m_pitch));
//    frontVector.y = glm::sin(glm::radians(g_cursorsData[g_cameraIndex].m_pitch));
//    frontVector.z = glm::sin(glm::radians(g_cursorsData[g_cameraIndex].m_yaw)) * glm::cos(glm::radians(g_cursorsData[g_cameraIndex].m_pitch));
//    g_cursorsData[g_cameraIndex].m_frontVector = glm::normalize(frontVector);

}












}















/*


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


}

*/





}


