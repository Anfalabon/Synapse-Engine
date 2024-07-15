#include "MouseEvents.hpp"

namespace Synapse
{

inline MouseEvents cursor;

//calculate the direction where the mouse/cursor is pointing to
//this calculates the vector where the camera will look at after certain changes in mouse input
//this should be inside 'Camera' class


void MouseEvents::MouseInput(GLFWwindow *window, double xpos, double ypos)
{


    if (cursor.m_movedForTheFirstTime)
    {
        cursor.m_lastX = xpos;
        cursor.m_lastY = ypos;

        cursor.m_movedForTheFirstTime = false;
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


}


void MouseEvents::OnMouseMovement(GLFWwindow *windowID, GLFWcursorposfun callback)
{
    glfwSetCursorPosCallback(windowID, callback);  //MouseEvents::MouseInput
}

void MouseEvents::SetInputMode(GLFWwindow *windowID, int mode, int value)
{
    glfwSetInputMode(windowID, mode, value);
}




}



