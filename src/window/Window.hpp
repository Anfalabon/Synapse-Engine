#pragma once

#include <core/Macros.hpp>
#include "debug/Log.hpp"

//#include "../debug/LOG.hpp"

#include <GLFW/glfw3.h>

#include <iostream>

namespace Synapse
{

class Window
{
public:

    Window() = default;
    Window(float WIDTH, float HEIGHT, const char *TITLE);
    ~Window()
    {
        //glfwTerminate();
    }


    [[nodiscard]] int8_t Init();
    void Resize();
    bool Restart();
    void ExitOnEscape();
    void GetKeyboardInput();

    __ALWAYS__INLINE__ void SwapBuffers(){glfwSwapBuffers(m_windowAddress);}
    __ALWAYS__INLINE__ void ShutDown(){glfwTerminate();}    //this is right now same as 'Terminate()'
    __ALWAYS__INLINE__ void PollEvents(){glfwPollEvents();}

    [[nodiscard]] __ALWAYS__INLINE__ bool IsRunning(){return (glfwWindowShouldClose(m_windowAddress)) ? false : true;};
    [[nodiscard]] __ALWAYS__INLINE__ GLFWwindow *WindowAddress(){return m_windowAddress;}
    [[nodiscard]] __ALWAYS__INLINE__ float WIDTH(){ return m_WIDTH; }
    [[nodiscard]] __ALWAYS__INLINE__ float HEIGHT(){ return m_HEIGHT; }

private:

    GLFWwindow *m_windowAddress;
    float     m_WIDTH;
    float     m_HEIGHT;
    const char *m_TITLE;
};



}





















