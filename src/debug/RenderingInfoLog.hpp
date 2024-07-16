#pragma once

#include <GLFW/glfw3.h>

#include <iostream>



namespace Synapse
{


namespace renderingInfo
{

inline double m_currentTimeSinceInit = glfwGetTime();
inline double m_previousTimeSinceInit = 0.0f;
inline std::size_t m_count = 0;

inline void FramesPerSecond(const float deltaTime = 0.0f)
{
    if (m_count > 0)
    {
        //m_currentTimeSinceInit = static_cast<double>(glfwGetTime());
        //double timeDifference = m_currentTimeSinceInit - m_previousTimeSinceInit;
        //m_previousTimeSinceInit = m_currentTimeSinceInit;

        //std::clog << "FPS:      " << 1 / timeDifference << '\n';


    }
    ++m_count;


    std::clog << "FPS:      " << 1 / deltaTime << '\n';
}

}


}