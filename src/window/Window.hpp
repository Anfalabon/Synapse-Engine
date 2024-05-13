
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../debug/LOG.hpp"


#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

class Window
{    
public:

    Window() = default;
    Window(GLfloat WIDTH, GLfloat HEIGHT, const char* TITLE);
    
    //void giveHint();
    //bool initSuccessLog();
    void resize();
    void exitOnEscape();
    void keyPressedLog(){LOG("key pressed!");}
    void getKeyboardInput();

    static void mouseInput(GLFWwindow* window ,double xpos, double ypos);    
    void swapBuffers();
    void terminate();
    void pollEvents();

    [[nodiscard]] bool running(); 
    [[nodiscard]] inline GLFWwindow *windowAddress(){return m_window;}
    [[nodiscard]] inline GLfloat WIDTH(){return m_WIDTH;}
    [[nodiscard]] inline GLfloat HEIGHT(){return m_HEIGHT;}

private:

    GLFWwindow  *m_window;    
    GLfloat m_WIDTH;
    GLfloat m_HEIGHT;
    const char* m_TITLE;
};

#endif  //file guard





















