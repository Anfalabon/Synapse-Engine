

#include "Window.hpp"

namespace Synapse
{


//Window::Window(GLfloat WIDTH, GLfloat HEIGHT, const char* TITLE)
//        : m_WIDTH(WIDTH), m_HEIGHT(HEIGHT), m_TITLE(TITLE)
//{
//    LOG("Running log from Window::Window()");
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    m_window = glfwCreateWindow(m_WIDTH, m_HEIGHT, m_TITLE, NULL, NULL);
//    if(!m_window)
//    {
//        std::cerr << "Failed to initialize window!" << '\n';
//        terminate();
//    }
//    glfwMakeContextCurrent(m_window);
//}
//


Window::Window(GLfloat WIDTH, GLfloat HEIGHT, const char* TITLE)
        : m_WIDTH(WIDTH), m_HEIGHT(HEIGHT), m_TITLE(TITLE)
{
    //m_window = glfwCreateWindow(m_WIDTH, m_HEIGHT, m_TITLE, NULL, NULL);
}

void Window::Init()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_WIDTH, m_HEIGHT, m_TITLE, NULL, NULL);
    if(!m_window)
    {
        std::cerr << "Failed to initialize window!" << '\n';
        this->Terminate();
    }
    glfwMakeContextCurrent(m_window);
}



void Window::ExitOnEscape()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}



void Window::Resize()
{
    if(glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
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

        glfwGetWindowSize(m_window, &tempW, &tempH);
    }
}


//get the input's from the user
void Window::GetKeyboardInput()
{
    Resize();
    ExitOnEscape();
}


void Window::Terminate()
{
    glfwTerminate();
}



void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}


bool Window::Running()
{
    if(glfwWindowShouldClose(m_window))
    {
        return false;
    }
    return true;

    //return (glfwWindowShouldClose(m_window)) ? false : true;
}


void Window::PollEvents()
{
    glfwPollEvents();
}




}










