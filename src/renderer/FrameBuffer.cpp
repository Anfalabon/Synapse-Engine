#include "FrameBuffer.hpp"


namespace Synapse
{

void FrameBuffer::SwapBuffers(GLFWwindow *windowAddress)
{
    glfwSwapBuffers(windowAddress);
}

}