#pragma once


#include "../debug/LOG.hpp"


#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>



namespace Synapse
{

class Window
{
public:

    Window() = default;
    Window(GLfloat WIDTH, GLfloat HEIGHT, const char *TITLE);

    //void giveHint();
    //bool initSuccessLog();
    void Init();
    void Resize();
    void ExitOnEscape();
    void KeyPressedLog(){ DEBUG::__LOG__MANAGER__::LOG("key pressed!"); }
    void GetKeyboardInput();

    static void MouseInput(GLFWwindow *window, double xpos, double ypos);

    void SwapBuffers();
    void Terminate();
    void PollEvents();

    [[nodiscard]] bool Running();
    [[nodiscard]] inline GLFWwindow *WindowAddress(){ return m_window; }
    [[nodiscard]] inline GLfloat WIDTH(){ return m_WIDTH; }
    [[nodiscard]] inline GLfloat HEIGHT(){ return m_HEIGHT; }

private:

    GLFWwindow *m_window;
    GLfloat m_WIDTH;
    GLfloat m_HEIGHT;
    const char *m_TITLE;
};



}





















