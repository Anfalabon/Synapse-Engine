#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Synapse
{

class MouseEvents
{
public:

    MouseEvents()
            : m_movedForTheFirstTime(true),
              m_lastX(1920.0f/2.0f),
              m_lastY(1080.0f/2.0f),
              m_yaw(-90.0f),
              m_pitch(0.0f),
              m_sensitivity(0.1f),
              m_isMoving(false),
              m_frontVector(glm::vec3(0.0f, 0.0f, 0.0f)){}

    ~MouseEvents() = default;

    static void MouseInput(GLFWwindow *windowID, double xpos, double ypos);
    static void OnMouseMovement(GLFWwindow *windowID, GLFWcursorposfun callback);
    static void SetInputMode(GLFWwindow* window, int mode, int value);

    void  SetLastX(){}
    void  SetLastY(){}
    bool  MovedForTheFirstTime(){return m_movedForTheFirstTime;}
    float GetLastX(){return m_lastX;}
    float GetLastY(){return m_lastY;}
    float GetYaw(){return m_yaw;}
    float GetPitch(){return m_pitch;}
    float GetSensitivity(){return m_sensitivity;}
    bool  IsMoving(){return m_isMoving;}

public:

    bool  m_movedForTheFirstTime;
    float m_lastX;
    float m_lastY;
    float m_yaw;
    float m_pitch;
    const float m_sensitivity;
    bool m_isMoving;
    glm::vec3 m_frontVector;

private:
    GLFWwindow *m_windowID;

};



}


