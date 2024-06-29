#include "PhysicsEngine.hpp"

#include <iostream>
#include <vector>
#include <omp.h>


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
    m_currentObjectHeight = m_objectMaxSize.y;    //will have to work on this
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

    //std::cout << std::boolalpha << "Point is inside the object: " << pointsInsideObject << '\n';

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
        if (m_pos.y >= 1.2f + 1.0f)    //right now the roof height is 1.2f but will change it cause it definately depends on the objects roof height
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



void Physics::OrbitAround(glm::vec3 &renderableObjectsPosition, const glm::vec3 &positionToOrbit, float &g_theta)
{
    //renderableObject->m_position.y += 1.0f/100.0f;
    //renderableObject->Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

//    float deltaX = renderableObject->m_position.x - positionToOrbit.x;
//    float deltaZ = renderableObject->m_position.z - positionToOrbit.z;

//    std::cout << "Delta X: " << deltaX << '\n';
//    std::cout << "Delta Z: " << deltaZ << '\n';

    //float r = glm::sqrt(deltaX*deltaX + deltaZ*deltaZ);
    float r = 3.0f;
    //std::cout << "Radius: " << r << '\n';

    //std::cout << renderableObjectsPosition.x << '\n';


    //renderableObjectsPosition.y += 1.0f/100.0f;
    renderableObjectsPosition.x = r * glm::cos(g_theta);
    renderableObjectsPosition.z = r * glm::sin(g_theta);



    //std::cout << "X pos: " << renderableObjectsPosition.x << '\n';
    //std::cout << "Z pos: " << renderableObjectsPosition.z << '\n';

    std::cout << "Is going to crash!" << '\n';

    //std::cout << "Theta: " << g_theta << '\n';
    g_theta += 0.1f;
    //m_theta += 0.1f;

    //std::cout << "Crashed before orbiting!" << '\n';
}


static float FastAbs(float value)
{
    unsigned int valueIEEE = *(unsigned int*)&value;
    valueIEEE &= 0x7FFFFFFF;
    return *(float*)&valueIEEE;
}


//the reaction force with the ground
void Physics::Bounce(glm::vec3 &velocity, glm::vec3 &initialVelocity)
{
    float materialConstant = 0.9f;
#if 1
    velocity.x = initialVelocity.x * materialConstant;
    velocity.y = glm::abs(initialVelocity.y) * materialConstant;    //will use faster absulote value function than glm::abs
    velocity.z = initialVelocity.z * materialConstant;

    initialVelocity.x = velocity.x;
    initialVelocity.y = velocity.y;
    initialVelocity.z = velocity.z;
#else
    velocity.x = velocity.x * materialConstant;
    velocity.y = FastAbs(velocity.y * materialConstant);
    velocity.z = velocity.z * materialConstant;
#endif
}


void Physics::Projectile(glm::vec3 &position, glm::vec3 &velocity, const float deltaTime, glm::vec3 &initialVelocity, bool addBouncing)
{
    float gravity = -0.1;
    float materialConstant = 0.9f;
    if (position.y < 0)
    {
        if(addBouncing)
        {
            this->Bounce(velocity, initialVelocity);
        }
        else
        {
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = 0.0f;
        }
    }

    std::cout << "Projectile!" << '\n';

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.z += velocity.z * deltaTime;

    velocity.y += gravity * deltaTime;
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


    omp_set_num_threads(0x8);
    #pragma omp parallel for
    for(std::size_t i=0; i<renderableObjects.size(); ++i)
    {
        //std::cout << "Checking for collision..." << '\n';
        this->SetCurrentObjectInfo(glm::vec3(renderableObjects[i]->m_position.x + 0.5f, renderableObjects[i]->m_position.y + 0.5f, renderableObjects[i]->m_position.z + 0.5f),
                                   glm::vec3(renderableObjects[i]->m_position.x - 0.5f, renderableObjects[i]->m_position.y - 0.5f, renderableObjects[i]->m_position.z - 0.5f));

        if(this->WasCollided())
        {
            //std::cout << "Collision detected!" << '\n';
            m_collided = true;
            m_posWhileCollision = m_pos;
            i = renderableObjects.size();
            //break;
        }
    }





//    if(renderableObjects.size() >= 3 && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
//    {
//        OrbitAround(renderableObjects, renderableObjects[0]->m_position);
//    }

}




}