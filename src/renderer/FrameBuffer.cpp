#include "FrameBuffer.hpp"


namespace Synapse
{


void FrameBuffer::FrameBufferSizeCallBack(GLFWwindow *windowAddress, int WIDTH, int HEIGHT)
{
    glViewport(0, 0, WIDTH, HEIGHT);
}


void FrameBuffer::SwapBuffers(GLFWwindow *windowAddress)
{
    glfwSwapBuffers(windowAddress);
}


}