#include "Camera.hpp"
#include "Cursor.hpp"   //include 'Cursor.hpp' after 'Camera.hpp' cause cursor includes GLFW and glm followed by and camera's inclusion of glad
#include "../debug/LOG.hpp"

#include <glm/glm.hpp>

#include <iostream>


namespace Synapse
{



//this should be inside the Engine class
void Camera::SetCameraMode(CAMERA_MODES M)
{
    M_CAMERA_MODE = M;
}


void Camera::AddShaderProgramID(GLuint shaderProgramID)
{
    //m_shaderProgramID = shaderProgramID;
    m_shaderProgramIDs.push_back(shaderProgramID);
    m_addedNewEntityShader = true;
}


void Camera::CalculateFrontVector(float yaw, float pitch)
{
    glm::vec3 frontVector;  //using this is maybe waste of memory when everytime mouse is moved
    frontVector.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    frontVector.y = glm::sin(glm::radians(pitch));
    frontVector.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    m_frontVector = glm::normalize(frontVector);
}



//void Camera::viewLocation(GLuint shaderProgramID)
void Camera::GetViewMatrixLocation()
{
//    for (auto shaderProgramID: m_shaderProgramIDs)
//    {
//        GLuint viewLocation = glGetUniformLocation(shaderProgramID, "view");
//        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_view));
//
//        //glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view", 1, GL_FALSE, glm::value_ptr(m_view)));
//    }

    if(m_shaderProgramIDs.size() > 0)
    {
        GLuint viewLocation = glGetUniformLocation(m_shaderProgramIDs[0], "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_view));
    }

}

//get the location of perspective matrix uniform in vertex shader
//void Camera::perspectiveLocation(GLuint shaderProgramID)
void Camera::GetPerspectiveMatrixLocation()
{
//    for (auto shaderProgramID: m_shaderProgramIDs)
//    {
//        GLuint perspectiveLocation = glGetUniformLocation(shaderProgramID, "perspective");
//        glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(m_perspective));
//
//        //glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "perspective", 1, GL_FALSE, glm::value_ptr(m_perspective)));
//    }

    if(m_shaderProgramIDs.size() > 0)
    {
        GLuint perspectiveLocation = glGetUniformLocation(m_shaderProgramIDs[0], "perspective");
        glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(m_perspective));
    }

}


void Camera::UpdateView(glm::mat4 &view)
{
    view = m_view;
}


void Camera::UpdateSpeed()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    const float cameraSpeedConstant = 10.0f;
    m_physics->m_speedCoefficient = cameraSpeedConstant * m_deltaTime;
}

//float deltaTime()
//{
//    float currentFrame = glfwGetTime();
//    m_deltaTime = currentFrame - m_lastFrame;
//    m_lastFrame = currentFrame;
//}

//here was the cursor calculations

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////will separate this physics part and generalize it for other Entities including Camera(maybe in the Physics Engine)//////


inline bool operator<=(const glm::vec3 &firstVec, const glm::vec3 &secondVec) noexcept
{
    return (firstVec.x <= secondVec.x &&
            firstVec.y <= secondVec.y &&
            firstVec.z <= secondVec.z);
}

inline bool operator>=(const glm::vec3 &firstVec, const glm::vec3 &secondVec) noexcept
{
    return (firstVec.x >= secondVec.x &&
            firstVec.y >= secondVec.y &&
            firstVec.z >= secondVec.z);
}

#if 0

void Camera::SetCurrentObjectInfo(const glm::vec3 &objectMaxSize, const glm::vec3 &objectMinSize)
{
    //initialize the max and min object range
    m_objectMaxSize = objectMaxSize;
    m_objectMinSize = objectMinSize;
    m_currentObjectHeight = m_objectMaxSize.y + 0.7;
}


//check for the collision with any object(for now it's the object located at the center)
bool Camera::WasCollided()
{
    bool pointsInsideObject = false;
    bool collisionOccured = false;


//    this->setCurrentObjectInfo(glm::vec3(0.9f, 1.2f, 0.9f),
//                               glm::vec3(-0.9f, -1.2f, -0.9f));

    //this was already done in this->ApplyPhysics() method
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

    if (m_cameraPos.x <= m_objectMaxSize.x + offset.x &&
        m_cameraPos.x >= m_objectMinSize.x - offset.x &&
        m_cameraPos.z <= m_objectMaxSize.z + offset.z &&
        m_cameraPos.z >= m_objectMinSize.z - offset.z &&
        m_cameraPos.y <= m_objectMaxSize.y + offset.y &&
        m_cameraPos.y >= m_objectMinSize.y - offset.y)
    {
        pointsInsideObject = true;
        m_cameraPosWhileCollision = m_cameraPos;
    }

    std::cout << std::boolalpha << "Point is inside the object: " << pointsInsideObject << '\n';

    m_isAtTheRoof = false;
    if (m_cameraPos.x <= m_objectMaxSize.x &&
        m_cameraPos.x >= m_objectMinSize.x &&
        m_cameraPos.z <= m_objectMaxSize.z &&
        m_cameraPos.z >= m_objectMinSize.z)
    {
        if (m_cameraPos.y >= m_currentObjectHeight)
        {
            m_isAtTheRoof = true;
        }
    }


    //check if the object was actually collided with the object
    //if the object is not at the top of the current object and it's collision with the object is true in x and z axis.
    return (pointsInsideObject && !m_isAtTheRoof);
}


void Camera::InitVelocity(const glm::vec3 &velocity)
{
    m_cameraVelocity = velocity;
}



struct PHYSICAL_CONSTANTS
{
    static constexpr float PI = 3.14159f;
    static constexpr float GRAVITY = 0.1f;
    static constexpr float DELTATIME = 0.27f;
};


void Camera::FallDown()
{
//if the player has reached the roof then he can't get down automatically for the height collision
//Tensor::Vector3 position = Tensor::Vector3(0.0f, 1.0f, 0.0f);



    float minHeight = m_initialHeight;

    std::cout << "Camera's current minHeight: " << minHeight << '\n';

    float gravity = -0.1f;
    float deltaTime = 0.27f;


    m_cameraPos.y += m_cameraVelocity.y * PHYSICAL_CONSTANTS::DELTATIME;
    m_cameraVelocity.y += PHYSICAL_CONSTANTS::GRAVITY * PHYSICAL_CONSTANTS::DELTATIME;

    //    motion.increaseHeight(m_cameraVelocity.y * deltaTime);
    //    motion.increaseVerticalVelocity(PhysicsEngine::PHYSICAL_CONSTANTS::GRAVITY * deltaTime);

    std::cout << "Velocity while falling down: " << m_cameraVelocity.y << '\n';
    std::cout << "Position while falling down: " << m_cameraPos.y << '\n';

    //for now the ground position is 0.0f
    if (m_cameraPos.y <= minHeight)
    {
        m_cameraPos.y = 0.0f;
        m_cameraVelocity.y = 0.774f;
        m_keepPhysicsRunning = false;
        //m_keepRunning = false;
        m_timeElapsed = 0.0f;
        //motion.reset();
    }

}


void Camera::Jump()
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

    m_cameraPos.y = m_cameraPos.y + m_cameraVelocity.y * PHYSICAL_CONSTANTS::DELTATIME;
    m_cameraVelocity.y = m_cameraVelocity.y + gravity * PHYSICAL_CONSTANTS::DELTATIME;

    std::cout << "Camera's vertical velocity: " << m_cameraVelocity.y << '\n';

    //max height reached by the camera when the initial velocity is 1: 5.08364

    //max height reached by the camera when the initial velocity is u : h = u * u/2g

    //m_cameraPos.y = m_cameraPos.y + m_cameraVelocity.y * deltaTime + gravity * deltaTime * deltaTime;

    //H2 = H1 + v2 * t
    //v2 = v1 + g * t

    //H2 = H1 + v1 * t + g * t * t

    if (m_cameraPos.y <= minHeight)
    {
        m_cameraPos.y = minHeight;
        m_cameraVelocity.y = 0.774f;
        //m_cameraVelocity.y = glm::sqrt(2 * gravity * jumpMaxHeight);
        m_jumped = false;
        m_timeElapsed = 0.0f;
    }

}


void Camera::ApplyVerticalMotions()
{
    std::cout << "Time elapsed: " << m_timeElapsed << '\n';

    if (m_jumped)
    {
        this->Jump();
    }

    // this->WasCollided();
    if (m_cameraPos.y <= m_currentObjectHeight && m_isAtTheRoof)
    {
        std::cout << "Camera is at the roof" << '\n';
        std::cout << "Camera velocity at the roof: " << m_cameraVelocity.y << '\n';
        m_cameraPos.y = m_currentObjectHeight;        
    }

    if (!m_jumped && !m_isAtTheRoof)
    {
        if (m_cameraPos.y >= 1.2f)
        {
            InitVelocity(glm::vec3(0.0f, -0.49f, 0.0f));
            //initVelocity(Tensor::Vector3(0.0f, -0.49f, 0.0f));

            m_timeElapsed = 0.455f;
            m_keepPhysicsRunning = true;
        }

        if (m_keepPhysicsRunning)
        {
            std::cout << "Camera's current velocity while falling down: " << m_cameraVelocity.y << '\n';
            this->FallDown();
        }
    }

    std::cout << "Camera height: " << m_cameraPos.y << '\n';

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Camera::ApplyPhysics()
{
    if (M_CAMERA_MODE == CAMERA_MODES::GAME_MODE)
    {
        std::cout << "CAMERA MODE: " << static_cast<uint8_t>(M_CAMERA_MODE) << '\n';
    }


    if (M_CAMERA_MODE == CAMERA_MODES::INSPECTION_MODE)
    {
        std::cout << "Camera is now in inspection mode" << '\n';
        return;
    }
    else if (M_CAMERA_MODE == CAMERA_MODES::GAME_MODE)
    {
        std::cout << "Camera is now in game mode" << '\n';
        this->ApplyVerticalMotions();

//        this->SetCurrentObjectInfo(glm::vec3(0.5f, 0.5f, 0.5f),
//                                   glm::vec3(-0.5, -0.5f, -0.5f));

        m_collided = false;
        m_collided = this->WasCollided();
        //m_collided = physics->WasCollided(m_cameraPos, m_currentObjectSize);
    }


}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Camera::IncreaseSpeed(GLFWwindow *m_window)
{
    //bool leftShiftPressed = false;
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        m_physics->m_speedCoefficient = m_physics->m_speedCoefficient * 3.0f;
        m_leftShiftPressed = true;
    }
}

void Camera::ApplyZoomInput(GLFWwindow *m_window)
{
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS &&
        glfwGetKey(m_window, GLFW_KEY_KP_ADD) == GLFW_PRESS && m_zoomValue > 5.0f)
    {
        m_zoomed = true;
        //m_zoomValue = 30.0f;
        m_zoomValue -= 5.0f;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS &&
             glfwGetKey(m_window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && m_zoomValue < 150.0f)
    {
        //m_zoomed = false;
        //m_zoomValue = 45.0f;
        m_zoomValue += 5.0f;
    }

    if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        m_zoomValue = 45.0f;
    }

    std::clog << "Current Field of view of the Camera: " << m_zoomValue << '\n';
    //will add scrolling for this
#ifdef ZOOM_SCROLLING
    if(m_zoomed)
    {
        --m_zoomValue;
    }
#endif


}



void Camera::ApplyCrouchInput(GLFWwindow *m_window)
{
    if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS)
    {
        m_physics->m_crouch = true;
        m_physics->m_pos.y -= 0.5f;
        if (m_physics->m_jumped)
        {
            m_physics->m_crouch = false;
            m_physics->m_pos.y += 0.5f;
        }
        //motion.decreaseHeight(0.5f);
        if (m_physics->m_pos.y <= -10.0f)
        {
            m_physics->m_pos.y = -9.0f;
        }
    }

}



void Camera::ApplyMovementInputs(GLFWwindow *m_window)
{
    using namespace Cursor;
    //this->CalculateFrontVector();

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        //        if(m_targetPos != m_cameraPosWhileCollision)
        //        {
        //            m_cameraPos.x = m_cameraPos.x + m_cameraSpeed * Calculate::m_directionVector.x * Calculate::m_rightAngleMovingSpeed;
        //            m_cameraPos.z = m_cameraPos.z + m_cameraSpeed * Calculate::m_directionVector.z * Calculate::m_rightAngleMovingSpeed;
        //        }

        //in game mode it can freely move in the ground plane only(x, z plane) but It can't move vertically.
        //and in inspection mode it can move in anywhere freely.
        if (M_CAMERA_MODE == CAMERA_MODES::GAME_MODE) [[likely]]
        {
            //if the camera collided with any object then it can't move further.
            //doing action on collision detection like this has a lot of problems
            //wil fix it.
            if (!m_physics->m_collided)
            {
                m_physics->m_pos.x = m_physics->m_pos.x + m_physics->m_speedCoefficient * Cursor::g_frontVector.x;
                m_physics->m_pos.z = m_physics->m_pos.z + m_physics->m_speedCoefficient * Cursor::g_frontVector.z;
            }
        }
        else if (M_CAMERA_MODE == CAMERA_MODES::INSPECTION_MODE) [[unlikely]]
        {
            m_physics->m_pos = m_physics->m_pos + m_physics->m_speedCoefficient * Cursor::g_frontVector;
        }

    }
    else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        //        if(!m_collided && M_ENGINE_MODE == 1)
        //        {
        m_physics->m_pos.x = m_physics->m_pos.x - m_physics->m_speedCoefficient * Cursor::g_frontVector.x;
        m_physics->m_pos.z = m_physics->m_pos.z - m_physics->m_speedCoefficient * Cursor::g_frontVector.z;
        //        }
        //        else if(M_ENGINE_MODE == 0)
        //        {
        //            m_cameraPos = m_cameraPos - m_cameraSpeed * Calculate::m_directionVector * Calculate::m_rightAngleMovingSpeed;
        //        }
    }
    else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_physics->m_pos += m_physics->m_speedCoefficient * glm::normalize(glm::cross(Cursor::g_frontVector, m_cameraUpVector));
    }
    else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_physics->m_pos -= m_physics->m_speedCoefficient * glm::normalize(glm::cross(Cursor::g_frontVector, m_cameraUpVector));
    }



    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout << "W and A pressed!" << '\n';
        m_physics->m_pos -= 1.0f * m_physics->m_speedCoefficient * glm::normalize(glm::cross(Cursor::g_frontVector, m_cameraUpVector));
    }

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "W and D pressed!" << '\n';
        m_physics->m_pos += 1.0f * m_physics->m_speedCoefficient * glm::normalize(glm::cross(Cursor::g_frontVector, m_cameraUpVector));
    }

    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout << "S and A pressed!" << '\n';
        m_physics->m_pos -= 1.0f * m_physics->m_speedCoefficient * glm::normalize(glm::cross(Cursor::g_frontVector, m_cameraUpVector));
    }

    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "S and D pressed!" << '\n';
        m_physics->m_pos += 1.0f * m_physics->m_speedCoefficient * glm::normalize(glm::cross(Cursor::g_frontVector, m_cameraUpVector));
    }


}





void Camera::ChangeCameraMode(GLFWwindow *m_window)
{
    //m_changeCameraMode = false;
    if(glfwGetKey(m_window, GLFW_KEY_O) == GLFW_PRESS)
    {
        //m_changeCameraMode = true;
        if(M_CAMERA_MODE == CAMERA_MODES::GAME_MODE)
        {
            M_CAMERA_MODE = CAMERA_MODES::INSPECTION_MODE;
        }
        else if(M_CAMERA_MODE == CAMERA_MODES::INSPECTION_MODE)
        {
            M_CAMERA_MODE = CAMERA_MODES::GAME_MODE;
            this->FallDown();
            //m_cameraPos.y = 0.0f;
        }
    }

    //M_CAMERA_MODE = (M_CAMERA_MODE == CAMERA_MODES::GAME_MODE) ? CAMERA_MODES::INSPECTION_MODE : CAMERA_MODES::GAME_MODE, m_cameraPos.y = 0.0f;

}



void Camera::EnableJumpingInput(GLFWwindow *m_window)
{
    //&& !m_collided
    if (KeyPressed(m_window, GLFW_KEY_SPACE) && !m_physics->m_jumped && M_CAMERA_MODE == CAMERA_MODES::GAME_MODE)
    {
        m_physics->m_jumped = true;
        m_physics->m_initialHeight = m_physics->m_pos.y;
    }
}


void Camera::ResetVerticalPositionInput(GLFWwindow *m_window)
{
    //reset the camera's vertical position
    if (KeyPressed(m_window, GLFW_KEY_LEFT_CONTROL) && KeyPressed(m_window, GLFW_KEY_R))
    {
        m_physics->m_pos.y = 0.0f;
    }
}



bool Camera::KeyPressed(GLFWwindow *m_window, const uint16_t KEYTOKEN)
{
    return (glfwGetKey(m_window, KEYTOKEN) == GLFW_PRESS);
}



//this function should only take user input
//will bind up other codes in other structures
void Camera::GetKeyboardInput(GLFWwindow *m_window)
{

    //---------------------------all of these will be inside 'events' directory----------------------------

    //speed up the camera if left shift was pressed


    std::cout << "Current Min height: " << m_physics->m_initialHeight << '\n';
    std::cout << "Current Camera speed is: " << m_physics->m_speedCoefficient << '\n';

    this->UpdateSpeed();
    this->IncreaseSpeed(m_window);
    this->EnableJumpingInput(m_window);
    this->ResetVerticalPositionInput(m_window);
    this->ApplyZoomInput(m_window);
    this->ApplyCrouchInput(m_window);
    this->ApplyMovementInputs(m_window);
    this->ChangeCameraMode(m_window);

    //this is a problem.
    //will need to fix it
    {
        //M_CAMERA_MODE = CAMERA_MODES::GAME_MODE;
        //M_CAMERA_MODE = CAMERA_MODES::INSPECTION_MODE;
    }

    //reset the camera speed
    if(m_leftShiftPressed)
    {
        this->UpdateSpeed();
    }
    m_leftShiftPressed = false;



    std::cout << "Camera going to crash!" << '\n';


}





void Camera::UpdatePerspective()
{
    m_perspective = glm::perspective(glm::radians(m_zoomValue), 1920.0f / 1080.0f, 0.1f, 100.0f);
}


//updateLookingTarget()
//updateViewMatrix()
void Camera::LookAtTarget()
{
    m_targetPos = m_physics->m_pos + Cursor::g_frontVector;

    DEBUG::__LOG__MANAGER__::LOG('\n');
    DEBUG::__LOG__MANAGER__::LOG("Camera's direction vector: ");
    DEBUG::__LOG__MANAGER__::GLM_LOG(Cursor::g_frontVector);
    DEBUG::__LOG__MANAGER__::LOG('\n');

    DEBUG::__LOG__MANAGER__::LOG("Camera's current Position: ");
    DEBUG::__LOG__MANAGER__::GLM_LOG(m_physics->m_pos);
    DEBUG::__LOG__MANAGER__::LOG('\n');

    DEBUG::__LOG__MANAGER__::LOG("Camera's target Position: ");
    DEBUG::__LOG__MANAGER__::GLM_LOG(m_targetPos);
    DEBUG::__LOG__MANAGER__::LOG('\n');


    DEBUG::__LOG__MANAGER__::LOG("Camera's delta time: ");
    DEBUG::__LOG__MANAGER__::LOG(m_deltaTime);
    DEBUG::__LOG__MANAGER__::LOG('\n');

    //glm::vec3 m_cameraWorldUp = glm::vec3(m_cameraUpVector.x , m_cameraUpVector.y, m_cameraUpVector.z);

    //this is for slow speed when the camera is pointing towards up-most or down-most
//    glm::vec3 m_cameraWorldUp = m_cameraUpVector;
//    glm::vec3 m_cameraRightVector = glm::normalize(glm::cross(Calculate::m_frontVector, m_cameraWorldUp));
//    m_cameraUpVector = glm::normalize(glm::cross(m_cameraRightVector, Calculate::m_frontVector));

    m_view = glm::lookAt(m_physics->m_pos, m_targetPos, m_cameraUpVector);
}

glm::vec3 Camera::GetFrontVector()
{
    return Cursor::g_frontVector;
}



void Camera::IsLookingAtEntity()
{
    glm::vec3 entityPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 differenceVec = entityPos - Cursor::g_frontVector;

    if (differenceVec.x <= m_physics->m_objectMaxSize.x &&
        differenceVec.x >= m_physics->m_objectMinSize.x &&
        differenceVec.z <= m_physics->m_objectMaxSize.z &&
        differenceVec.z >= m_physics->m_objectMinSize.z &&
        differenceVec.y <= m_physics->m_objectMaxSize.y &&
        differenceVec.y >= m_physics->m_objectMinSize.y)
    {
        std::cout << "Camera looking at cube!" << '\n';
    }
}



void Camera::Update()
{
    //this->getKeyboardInput();
    std::cout << "Total shader program ID's: " << m_shaderProgramIDs.size() << '\n';

    //this->ChangeCameraMode();
    //this->UpdateCameraSpeed();
    //this->ApplyPhysics();
    m_physics->Apply(); //this doesn't check Camera mode and just simply applies physics regarding of cameras actual mode
    this->GetViewMatrixLocation();
    this->GetPerspectiveMatrixLocation();
    this->UpdatePerspective();
    this->LookAtTarget();
}


//static function
void Camera::SetupMouse(GLFWwindow *window)
{
    glfwSetCursorPosCallback(window, Cursor::mouseInput);  //MouseEvents::mouseInput
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}



}