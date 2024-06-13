#pragma once

#include "../debug/LOG.hpp"

#include <GLFW/glfw3.h>

#include <iostream>

namespace Synapse
{

class Window
{
public:

    Window() = default;
    Window(GLfloat WIDTH, GLfloat HEIGHT, const char *TITLE);
    ~Window()
    {
        //glfwTerminate();
    }


    [[nodiscard]] int8_t Init();
    void Resize();
    void ExitOnEscape();
    void KeyPressedLog(){ DEBUG::__LOG__MANAGER__::LOG("key pressed!"); }
    void GetKeyboardInput();

    static void MouseInput(GLFWwindow *window, double xpos, double ypos);

    void SwapBuffers();
    void Terminate();
    void PollEvents();

    [[nodiscard]] bool IsRunning();
    [[nodiscard]] inline GLFWwindow *WindowAddress(){ return m_windowAddress; }
    [[nodiscard]] inline GLfloat WIDTH(){ return m_WIDTH; }
    [[nodiscard]] inline GLfloat HEIGHT(){ return m_HEIGHT; }

private:

    GLFWwindow *m_windowAddress;
    GLfloat     m_WIDTH;
    GLfloat     m_HEIGHT;
    const char *m_TITLE;
};



}





















