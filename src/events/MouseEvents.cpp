#include "MouseEvents.hpp"

namespace Synapse
{

inline MouseEvents cursor;

//calculate the direction where the mouse/cursor is pointing to
//this calculates the vector where the camera will look at after certain changes in mouse input
//this should be inside 'Camera' class
void MouseEvents::CalculateFrontVector()
{
    glm::vec3 frontVector;  //using this is maybe waste of memory when everytime mouse is moved
    frontVector.x = glm::cos(glm::radians(cursor.m_yaw)) * glm::cos(glm::radians(cursor.m_pitch));
    frontVector.y = glm::sin(glm::radians(cursor.m_pitch));
    frontVector.z = glm::sin(glm::radians(cursor.m_yaw)) * glm::cos(glm::radians(cursor.m_pitch));
    cursor.m_frontVector = glm::normalize(cursor.m_frontVector);
}


void MouseEvents::mouseInput(GLFWwindow *window, double xpos, double ypos)
{


    if (cursor.m_movedMouseForTheFirstTime)
    {
        cursor.m_lastX = xpos;
        cursor.m_lastY = ypos;

        cursor.m_movedMouseForTheFirstTime = false;
    }

    float Xoffset = xpos - cursor.m_lastX;
    float Yoffset = cursor.m_lastY - ypos;

    cursor.m_lastX = xpos;
    cursor.m_lastY = ypos;

    //calculate the offset
    Xoffset = Xoffset * cursor.m_sensitivity;
    Yoffset = Yoffset * cursor.m_sensitivity;

    //calculate yaw and pitch
    cursor.m_yaw = cursor.m_yaw + Xoffset;
    cursor.m_pitch = cursor.m_pitch + Yoffset;
    //set the moving speed constant of the camera when't it's pointing at 90 degree or right angle
    //cause camera speed is slower at 90 or -90 degree pitch //but this is still not that good cause it only works for some degrees
    if (cursor.m_pitch > 89.0f)
    {
        cursor.m_pitch = 89.0f;
    }
    else if (cursor.m_pitch < -89.0f)
    {
        cursor.m_pitch = -89.0f;
    }

    //Camera::CalculateFrontVector(cursor.m_yaw, cursor.m_pitch, cursor.m_frontVector);
    MouseEvents::CalculateFrontVector();

}




}



