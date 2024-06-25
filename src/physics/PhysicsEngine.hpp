#pragma once

#include "../scene/Entities.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

namespace Synapse
{

class Physics
{
public:

    struct PHYSICAL_CONSTANTS
    {
        static constexpr float PI = 3.14159f;
        static constexpr float GRAVITY = 0.1f;
        static constexpr float DELTATIME = 0.27f;
    };

    Physics() = default;
    //virtual ~Physics() = default;

    void CalculateDeltaTime();
    void SetCurrentObjectInfo(const glm::vec3 &objectMaxSize, const glm::vec3 &objectMinSize);
    void Reset(){}
    bool WasCollided();
    void FallDown();
    void Jump();
    void ApplyVerticalMotions();
    void Apply(const std::vector<Synapse::RenderableObject*> &renderableObjects);





//protected:


    //inside physics class we don't need these data's as our design style for utilizing Physics in the Engine doesn't match nicely with this
    //every scene object will have it's own data sets like this if physics is needed to be implemented on it.
    //so basically the owner of these data sets is not going to be 'Physics' class or any of it's derived classes.
    //this 'Physics' class and it's derived classed will only operate on objects


    //So, for instance it should be the following (according to the design style):
    //Camera *camera = new Camera();
    //Physics *physics;
    //physics->Jump(camera);
    //bool wasCollidedWithObject = physics->WasCollided(camera);

    //rather than the following:
    //Camera *camera = new Camera();
    //camera->physics->Jump();

    //will name it 'm_pos' from 'm_entityPos' and same with 'm_entityVelocity'


    glm::vec3 m_pos = glm::vec3(3.0f, 0.0f, 3.0f);
    glm::vec3 m_velocity = glm::vec3(0.0f, 0.7740f, 0.0f);

    glm::vec3 m_posWhileCollision;
    glm::vec3 m_objectMaxSize;
    glm::vec3 m_objectMinSize;

    bool m_jumped = false;
    bool m_collided = false;
    bool m_crouch = false;
    bool m_isAtTheRoof = false;
    bool m_keepPhysicsRunning = false;

    float m_initialHeight = 0.0f;
    float m_currentObjectHeight = 0.0f;

    float m_speedCoefficient;
    float m_timeElapsed = 0.0f;
    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;


};

}


