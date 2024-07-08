#include "../renderer/FrameBuffer.hpp"  //here including it before the 'Window.hpp' becuase glad should be included before any(or here GLFW) header
#include "Window.hpp"

namespace Synapse
{





Window::Window(GLfloat WIDTH, GLfloat HEIGHT, const char* TITLE)
        : m_WIDTH(WIDTH), m_HEIGHT(HEIGHT), m_TITLE(TITLE)
{
    //m_window = glfwCreateWindow(m_WIDTH, m_HEIGHT, m_TITLE, NULL, NULL);
}



//void Window::FrameBufferSizeCallback(GLFWwindow *window, int WIDTH, int HEIGHT)
//{
//    glViewport(0, 0, WIDTH, HEIGHT);
//}



int8_t Window::Init()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_windowAddress = glfwCreateWindow(m_WIDTH, m_HEIGHT, m_TITLE, NULL, NULL);
    if(!m_windowAddress)
    {
        std::cerr << "Failed to initialize window!" << '\n';
        this->ShutDown();
        return -1;
    }
    glfwMakeContextCurrent(m_windowAddress);
    glfwSetFramebufferSizeCallback(m_windowAddress, FrameBuffer::FrameBufferSizeCallBack);

    return 1;
}



void Window::ExitOnEscape()
{
    if(glfwGetKey(m_windowAddress, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_windowAddress, true);
    }
}



void Window::Resize()
{
    if(glfwGetKey(m_windowAddress, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS &&
       glfwGetKey(m_windowAddress, GLFW_KEY_R) == GLFW_PRESS &&
       glfwGetKey(m_windowAddress, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
    {
        if(m_WIDTH == 1980.0f && m_HEIGHT == 1080.0f)
        {
            m_WIDTH = 800.0f;
            m_HEIGHT = 600.0f;
        }
        else if(m_WIDTH == 800.0f && m_HEIGHT == 600.0f)
        {
            m_WIDTH = 1980.0f;
            m_HEIGHT = 1080.0f;
        }

        int tempW = static_cast<int>(m_WIDTH);
        int tempH = static_cast<int>(m_HEIGHT);

        glfwGetWindowSize(m_windowAddress, &tempW, &tempH);
    }
}


//get the input's from the user
void Window::GetKeyboardInput()
{
    this->Resize();
    this->ExitOnEscape();
}


void Window::SwapBuffers()
{
    glfwSwapBuffers(m_windowAddress);
}


bool Window::IsRunning()
{
//    if(glfwWindowShouldClose(m_windowAddress))
//    {
//        return false;
//    }
//    return true;

    return (glfwWindowShouldClose(m_windowAddress)) ? false : true;
}


void Window::PollEvents()
{
    glfwPollEvents();
}


void Window::ShutDown()
{
    glfwTerminate();
}




}










