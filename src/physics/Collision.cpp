#include "Collision.hpp"

#include <iostream>


namespace Synapse
{

void Collision::SetCurrentObjectInfo(const glm::vec3 &objectMaxSize, const glm::vec3 &objectMinSize)
{
    //initialize the max and min object range
    m_objectMaxSize = objectMaxSize;
    m_objectMinSize = objectMinSize;
    m_currentObjectHeight = m_objectMaxSize.y + 0.7;
}

bool Collision::WasCollided()
{
    bool pointsInsideObject = false;
    bool collisionOccured = false;


//    this->setCurrentObjectInfo(glm::vec3(0.9f, 1.2f, 0.9f),
//                               glm::vec3(-0.9f, -1.2f, -0.9f));

    this->SetCurrentObjectInfo(glm::vec3(0.5f, 0.5f, 0.5f),
                               glm::vec3(-0.5, -0.5f, -0.5f));


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
        m_posWhileCollision = m_pos;
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





}

