#include "Kinematics.hpp"

#include <iostream>


namespace Synapse
{


void Kinematics::FallDown()
{
    //if the player has reached the roof then he can't get down automatically for the height collision
    //Tensor::Vector3 position = Tensor::Vector3(0.0f, 1.0f, 0.0f);

    float minHeight = m_initialHeight;

    std::cout << "Camera's current minHeight: " << minHeight << '\n';

    float deltaTime = 0.27f;

    m_pos.y += m_velocity.y * PHYSICAL_CONSTANTS::DELTATIME;
    m_velocity.y += PHYSICAL_CONSTANTS::GRAVITY * PHYSICAL_CONSTANTS::DELTATIME;

    std::cout << "Velocity while falling down: " << m_velocity.y << '\n';
    std::cout << "Position while falling down: " << m_pos.y << '\n';

    //for now the ground position is 0.0f
    if (m_pos.y <= minHeight)
    {
        m_pos.y = 0.0f;
        m_velocity.y = 0.774f;
        m_keepPhysicsRunning = false;
        m_timeElapsed = 0.0f;

        //motion.reset();
    }

}


void Kinematics::Jump()
{
    //will make it something like: It will jump from it's current height(the initial height doesn't have to be zero)

    float minHeight = m_initialHeight;
    //float minHeight = 0.0f;
    if (m_isAtTheRoof)
    {
        minHeight = m_currentObjectHeight; //the current object it will jump on
    }

    std::cout << "Min current height: " << minHeight << '\n';

    float deltaTime = 0.27f;

    m_pos.y += m_velocity.y * PHYSICAL_CONSTANTS::DELTATIME;
    m_velocity.y += PHYSICAL_CONSTANTS::GRAVITY * PHYSICAL_CONSTANTS::DELTATIME;

    std::cout << "Camera's vertical velocity: " << m_velocity.y << '\n';

    //max height reached by the camera when the initial velocity is 1: 5.08364

    //max height reached by the camera when the initial velocity is u : h = u * u/2g

    //m_cameraPos.y = m_cameraPos.y + m_cameraVelocity.y * deltaTime + gravity * deltaTime * deltaTime;

    //H2 = H1 + v2 * t
    //v2 = v1 + g * t

    //H2 = H1 + v1 * t + g * t * t

    if (m_pos.y <= minHeight)
    {
        m_pos.y = minHeight;
        m_velocity.y = 0.774f;
        //m_cameraVelocity.y = glm::sqrt(2 * gravity * jumpMaxHeight);
        m_jumped = false;
        m_timeElapsed = 0.0f;
    }
}


void Kinematics::ApplyVerticalMotions()
{

    std::cout << "Time elapsed: " << m_timeElapsed << '\n';

    if (m_jumped)
    {
        this->Jump();
    }

    // this->wasCollided();
    if (m_pos.y <= m_currentObjectHeight && m_isAtTheRoof)
    {
        std::cout << "Camera is at the roof" << '\n';
        std::cout << "Camera velocity at the roof: " << m_velocity.y << '\n';
        m_pos.y = m_currentObjectHeight;
    }

    if (!m_jumped && !m_isAtTheRoof)
    {
        if (m_pos.y >= 1.2f)
        {
            m_velocity.y = -0.49f;
            //InitVelocity(glm::vec3(0.0f, -0.49f, 0.0f));
            //initVelocity(Tensor::Vector3(0.0f, -0.49f, 0.0f));

            m_timeElapsed = 0.455f;
            m_keepPhysicsRunning = true;
        }

        if (m_keepPhysicsRunning)
        {
            std::cout << "Camera's current velocity while falling down: " << m_velocity.y << '\n';
            this->FallDown();
        }
    }

    std::cout << "Camera height: " << m_pos.y << '\n';

}





}