

#include "Window.hpp"



Window::Window(GLfloat WIDTH, GLfloat HEIGHT, const char* TITLE)
        : m_WIDTH(WIDTH), m_HEIGHT(HEIGHT), m_TITLE(TITLE)
{
    LOG("Running log from Window::Window()");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_WIDTH, m_HEIGHT, m_TITLE, NULL, NULL);
    if(!m_window)
    {
        std::cerr << "Failed to initialize window!" << '\n';
        terminate();
    }
    glfwMakeContextCurrent(m_window);
}



void Window::exitOnEscape()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}



void Window::resize()
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
void Window::getKeyboardInput()
{
    resize();    
    exitOnEscape();
}


void Window::terminate()
{
    glfwTerminate();
}



void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}


bool Window::running()
{
    if(glfwWindowShouldClose(m_window))
    {
        return false;
    }
    return true;
}


void Window::pollEvents()
{
    glfwPollEvents();
}











