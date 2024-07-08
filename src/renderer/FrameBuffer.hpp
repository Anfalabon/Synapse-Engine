#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>


namespace Synapse
{


class FrameBuffer
{
public:
    FrameBuffer() = default;
    ~FrameBuffer() = default;

    static void FrameBufferSizeCallBack(GLFWwindow *windowAddress, int WIDTH, int HEIGHT);
    void SwapBuffers(GLFWwindow *windowAddress);

private:
};


}