#pragma once

#include <GLFW/glfw3.h>

namespace Synapse
{

class KeyboardEvents
{
public:
    KeyboardEvents(GLFWwindow *windowID)
    : m_windowID(windowID){}
    ~KeyboardEvents() = default;

    [[nodiscard]] inline bool KeyPressed(GLenum keyToken)
    {
        return (glfwGetKey(m_windowID, keyToken) == GLFW_PRESS);
    }

private:
    GLFWwindow *m_windowID;
};


}