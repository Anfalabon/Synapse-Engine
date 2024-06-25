#include "PhysicsEngine.hpp"

#include <iostream>
#include <vector>


namespace Synapse
{

void Physics::CalculateDeltaTime()
{
    float currentFrame = glfwGetTime();
    float currentDeltaTime = m_deltaTime;
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
}

void Physics::SetCurrentObjectInfo(const glm::vec3 &objectMaxSize, const glm::vec3 &objectMinSize)
{
    //initialize the max and min object range
    m_objectMaxSize = objectMaxSize;
    m_objectMinSize = objectMinSize;
    m_currentObjectHeight = m_objectMaxSize.y + 0.7;
}


//check for the collision with any object(for now it's the object located at the center)
bool Physics::WasCollided()
{
    bool pointsInsideObject = false;
    bool collisionOccured = false;


//    this->setCurrentObjectInfo(glm::vec3(0.9f, 1.2f, 0.9f),
//                               glm::vec3(-0.9f, -1.2f, -0.9f));

    //this was already done in this->ApplyPhysics() method

//float offset = 0.3f;    //offset is for more accurate collision with the object to check for the height collision

//this is because we need to detect the camera's collision with the object earlier than the camera's actual collision with the object
    glm::vec3 offset = glm::vec3(0.3f, 0.3f, 0.3f);

//    if (m_cameraPos <= m_objectMaxSize + offset &&
//        m_cameraPos >= m_objectMinSize - offset)
//    {
//        pointsInsideObject = true;
//        m_cameraPosWhileCollision = m_cameraPos;
//    }


//check if all the points of camera position is inside the object(collision detection)
//we are neglecting the minimum y-axis detection cause we assume everything starts from height 0.0f(maybe will change it in the future)

    if (m_pos.x <= m_objectMaxSize.x + offset.x &&
        m_pos.x >= m_objectMinSize.x - offset.x &&
        m_pos.z <= m_objectMaxSize.z + offset.z &&
        m_pos.z >= m_objectMinSize.z - offset.z &&
        m_pos.y <= m_objectMaxSize.y + offset.y &&
        m_pos.y >= m_objectMinSize.y - offset.y)
    {
        pointsInsideObject = true;
        //m_cameraPosWhileCollision = m_cameraPos;
    }

    std::cout << std::boolalpha << "Point is inside the object: " << pointsInsideObject << '\n';

    m_isAtTheRoof = false;
    if (m_pos.x <= m_objectMaxSize.x &&
        m_pos.x >= m_objectMinSize.x &&
        m_pos.z <= m_objectMaxSize.z &&
        m_pos.z >= m_objectMinSize.z)
    {
        if (m_pos.y >= m_currentObjectHeight)
        {
            m_isAtTheRoof = true;
        }
    }


    //check if the object was actually collided with the object
    //if the object is not at the top of the current object and it's collision with the object is true in x and z axis.
    return (pointsInsideObject && !m_isAtTheRoof);
}



void Physics::FallDown()
{
//if the player has reached the roof then he can't get down automatically for the height collision
//Tensor::Vector3 position = Tensor::Vector3(0.0f, 1.0f, 0.0f);

    float minHeight = m_initialHeight;

    std::cout << "Camera's current minHeight: " << minHeight << '\n';

    float gravity = -0.1f;
    float deltaTime = 0.27f;


    m_pos.y += m_velocity.y * PHYSICAL_CONSTANTS::DELTATIME;
    m_velocity.y += PHYSICAL_CONSTANTS::GRAVITY * PHYSICAL_CONSTANTS::DELTATIME;

    //    motion.increaseHeight(m_cameraVelocity.y * deltaTime);
    //    motion.increaseVerticalVelocity(PhysicsEngine::PHYSICAL_CONSTANTS::GRAVITY * deltaTime);

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


void Physics::Jump()
{
    //will make it something like: It will jump from it's current height(the initial height doesn't have to be zero)

    float minHeight = m_initialHeight;
    //float minHeight = 0.0f;
    if (m_isAtTheRoof)
    {
        minHeight = m_currentObjectHeight; //the current object it will jump on
    }

    std::cout << "Min current height: " << minHeight << '\n';

    float gravity = -0.1f;
    float deltaTime = 0.27f;     //0.167f is a standard delta time but to make it faster it has been changed

    m_pos.y = m_pos.y + m_velocity.y * PHYSICAL_CONSTANTS::DELTATIME;
    m_velocity.y = m_velocity.y + gravity * PHYSICAL_CONSTANTS::DELTATIME;

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


void Physics::ApplyVerticalMotions()
{
    std::cout << "Time elapsed: " << m_timeElapsed << '\n';

    if (m_jumped)
    {
        this->Jump();
    }

    // this->WasCollided();
    if (m_pos.y <= m_currentObjectHeight && m_isAtTheRoof)
    {
        std::cout << "Camera is at the roof" << '\n';
        std::cout << "Camera velocity at the roof: " << m_velocity.y << '\n';
        m_pos.y = m_currentObjectHeight;
    }

    if (!m_jumped && !m_isAtTheRoof)
    {
        if (m_pos.y >= 1.2f)    //right now the roof height is 1.2f but will change it cause it definately depends on the objects roof height
        {
            m_velocity.y = -0.49;
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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Physics::Apply(const std::vector<Synapse::RenderableObject*> &renderableObjects)
{
    std::cout << "Camera is now in game mode" << '\n';
    this->ApplyVerticalMotions();

//    this->SetCurrentObjectInfo(glm::vec3(0.5f, 0.5f, 0.5f),
//                               glm::vec3(-0.5, -0.5f, -0.5f));

    m_collided = false;
    //m_collided = this->WasCollided();

    for(RenderableObject* renderableObject : renderableObjects)
    {
        std::cout << "Checking for collision..." << '\n';
        this->SetCurrentObjectInfo(glm::vec3(renderableObject->m_position.x + 0.5f, renderableObject->m_position.y + 0.5f, renderableObject->m_position.z + 0.5f),
                                   glm::vec3(renderableObject->m_position.x - 0.5f, renderableObject->m_position.y - 0.5f, renderableObject->m_position.z - 0.5f));

        std::cout << "Total renderable entities: " << renderableObjects.size() << '\n';
        std::cout << "x pos: " << renderableObject->m_position.x << '\n';
        std::cout << "y pos: " << renderableObject->m_position.y << '\n';
        std::cout << "z pos: " << renderableObject->m_position.z << '\n';


        if(this->WasCollided())
        {
            std::cout << "Collision detected!" << '\n';
            m_collided = true;
            break;
        }
    }

}




}