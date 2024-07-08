#pragma once

#include <GLFW/glfw3.h>


namespace Synapse
{

class FrameBuffer
{
public:
    FrameBuffer() = default;
    ~FrameBuffer() = default;

    void SwapBuffers(GLFWwindow *windowAddress);

private:
};


}