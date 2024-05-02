

#include "Camera.hpp"
#include "../debug/LOG.hpp"
#include "../debug/RenderingInfoLog.hpp"

#include <thread>


void Camera::setEngineMode(const uint8_t ENGINE_MODE)
{
    M_ENGINE_MODE = ENGINE_MODE;
}


void Camera::setShaderProgramID(GLuint shaderProgramID)
{
    //m_shaderProgramID = shaderProgramID;
    m_shaderProgramIDs.push_back(shaderProgramID);
    m_addedNewEntityShader = true;
}


//get the location of perspective matrix uniform in vertex shader
//void Camera::perspectiveLocation(GLuint shaderProgramID)
void Camera::perspectiveLocation()
{
    for(auto shaderProgramID : m_shaderProgramIDs)
    {
        GLuint perspectiveLocation = glGetUniformLocation(shaderProgramID, "perspective");
        glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(m_perspective));
    }
}

//void Camera::viewLocation(GLuint shaderProgramID)
void Camera::viewLocation()
{
    for(auto shaderProgramID : m_shaderProgramIDs)
    {
        GLuint viewLocation = glGetUniformLocation(shaderProgramID, "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m_view));
    }
}

void Camera::updatePerspective()
{
    m_perspective = glm::perspective(glm::radians(m_zoomValue), 1920.0f/1080.0f, 0.1f, 100.0f);
}


void Camera::setCameraSpeed()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    const float cameraSpeedConstant = 10.0f;
    m_cameraSpeed = cameraSpeedConstant * m_deltaTime;
}



namespace Calculate
{

float m_lastX = 1920.0f/2.0f;
float m_lastY = 1080.0f/2.0f;
float m_yaw = -90.0f;
float m_pitch = 0.0f;
float m_rightAngleMovingSpeed = 1.0f;
const float m_sensitivity = 0.1f;

bool m_firstMouse = true;
bool m_isMouseMoving = false;
glm::vec3 m_directionVector = glm::vec3(0.0f, 0.0f, 0.0f);



//calculate the direction where the mouse/cursor is pointing to
//this calculates the vector where the camera will look at after certain changes in mouse input
void calculateDirectionVector()
{
    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    direction.y = glm::sin(glm::radians(m_pitch));
    direction.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    m_directionVector = glm::normalize(direction);
}


void mouseInput(GLFWwindow* window, double xpos, double ypos)
{
    m_isMouseMoving = true;
    if(m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;

        m_firstMouse = false;
    }

    float Xoffset = xpos - m_lastX;
    float Yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;
    
    //calculate the offset
    Xoffset = Xoffset * m_sensitivity;
    Yoffset = Yoffset * m_sensitivity;

    //calculate yaw and pitch
    m_yaw = m_yaw + Xoffset;
    m_pitch = m_pitch + Yoffset;
    //set the moving speed constant of the camera when't it's pointing at 90 degree or right angle
    //cause camera speed is slower at 90 or -90 degree pitch //but this is still not that good cause it only works for some degrees
    if(m_pitch > 89.0f)
    {
        m_pitch = 89.0f;
        m_rightAngleMovingSpeed = 3.6f;
    }
    else if(m_pitch < -89.0f)
    {
        m_pitch = -89.0f;
        m_rightAngleMovingSpeed = 3.6f;
    }
    else
    {
        m_rightAngleMovingSpeed = 1.0f;
    }

    calculateDirectionVector();

}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////will separate this physics part and generalize it for other Entities including Camera/////////////////////


namespace glm
{
    inline bool operator<=(const vec3 &firstVec, const vec3 &secondVec) noexcept
    {
        return (firstVec.x <= secondVec.x &&
                firstVec.y <= secondVec.y &&
                firstVec.z <= secondVec.z);
    }

    inline bool operator>=(const vec3 &firstVec, const vec3 &secondVec) noexcept
    {
        return (firstVec.x >= secondVec.x &&
                firstVec.y >= secondVec.y &&
                firstVec.z >= secondVec.z);
    }
}


void Camera::setCurrentObjectInfo(const glm::vec3 &objectMaxSize,
                                  const glm::vec3 &objectMinSize)
{
    //initialize the max and min object range
    m_objectMaxSize = objectMaxSize;
    m_objectMinSize = objectMinSize;
    m_currentObjectHeight = m_objectMaxSize.y + 0.7;
}



//check for the collision with any object(for now it's the object located at the center)
bool Camera::wasCollided() {
    bool pointsInsideObject = false;
    bool collisionOccured = false;


//    this->setCurrentObjectInfo(glm::vec3(0.9f, 1.2f, 0.9f),
//                               glm::vec3(-0.9f, -1.2f, -0.9f));

    this->setCurrentObjectInfo(glm::vec3(0.5f, 0.5f, 0.5f),
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

    if(m_cameraPos.x <= m_objectMaxSize.x + offset.x &&
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
    if(m_cameraPos.x <= m_objectMaxSize.x &&
       m_cameraPos.x >= m_objectMinSize.x &&
       m_cameraPos.z <= m_objectMaxSize.z &&
       m_cameraPos.z >= m_objectMinSize.z)
    {
        if(m_cameraPos.y >= m_currentObjectHeight)
        {
            m_isAtTheRoof = true;            
        }
    }


    //check if the object was actually collided with the object
    //if the object is not at the top of the current object and it's collision with the object is true in x and z axis.
    return (pointsInsideObject && !m_isAtTheRoof);
}





void Camera::initVelocity(const glm::vec3 &velocity)
{
    m_cameraVelocity = velocity;
}



void Camera::fallDown()
{
    //if the player has reached the roof then he can't get down automatically for the height collision
    //Tensor::Vector3 position = Tensor::Vector3(0.0f, 1.0f, 0.0f);

    float minHeight = m_initialHeight;

    std::cout << "Camera's current minHeight: " << minHeight << '\n';

    float gravity = -0.1f;
    float deltaTime = 0.27f;

    m_cameraPos.y = m_cameraPos.y + m_cameraVelocity.y * deltaTime;
    m_cameraVelocity.y = m_cameraVelocity.y + gravity * deltaTime;

    std::cout << "Velocity while falling down: " << m_cameraVelocity.y << '\n';
    std::cout << "Position while falling down: " << m_cameraPos.y << '\n';

    //for now the ground position is 0.0f
    if(m_cameraPos.y <= minHeight)
    {
        m_cameraPos.y = 0.0f;
        m_cameraVelocity.y = 0.774f;
        m_keepRunning = false;
        m_timeElapsed = 0.0f;
    }

}



void Camera::jump()
{
    //will make it something like: It will jump from it's current height(the initial height doesn't have to be zero)

    float minHeight = m_initialHeight;
    //float minHeight = 0.0f;
    if(m_isAtTheRoof)
    {
        minHeight = m_currentObjectHeight; //the current object it will jump on
    }

    std::cout << "Min current height: " << minHeight << '\n';

    float gravity = -0.1f;    
    float deltaTime = 0.27f;     //0.167f is a standard delta time but to make it faster it has been changed   
    
    m_cameraPos.y = m_cameraPos.y + m_cameraVelocity.y * deltaTime;
    m_cameraVelocity.y = m_cameraVelocity.y + gravity * deltaTime;

    std::cout << "Camera's vertical velocity: " << m_cameraVelocity.y << '\n';

    //max height reached by the camera when the initial velocity is 1: 5.08364

    //max height reached by the camera when the initial velocity is u : h = u * u/2g

    //m_cameraPos.y = m_cameraPos.y + m_cameraVelocity.y * deltaTime + gravity * deltaTime * deltaTime;
    
    //H2 = H1 + v2 * t
    //v2 = v1 + g * t

    //H2 = H1 + v1 * t + g * t * t

    if(m_cameraPos.y <= minHeight)
    {
        m_cameraPos.y = minHeight;
        m_cameraVelocity.y = 0.774f;
        //m_cameraVelocity.y = glm::sqrt(2 * gravity * jumpMaxHeight);
        m_jumped = false;
        m_timeElapsed = 0.0f;
    }
}



void Camera::verticalMotion()
{

    std::cout << "Time elapsed: " << m_timeElapsed << '\n';

    if(m_jumped)
    {
        this->jump();
    }
    
    // this->wasCollided();
    if(m_cameraPos.y <= m_currentObjectHeight && m_isAtTheRoof)
    {
        std::cout << "Camera is at the roof" << '\n';
        std::cout << "Camera velocity at the roof: " << m_cameraVelocity.y << '\n';
        m_cameraPos.y = m_currentObjectHeight;
    }
    
    if(!m_jumped && !m_isAtTheRoof)
    {
        if(m_cameraPos.y >= 1.2f)
        {
            //initVelocity(glm::vec3(0.0f, -0.49f, 0.0f));
            initVelocity(Tensor::Vector3(0.0f, -0.49f, 0.0f));
            m_timeElapsed = 0.455f;
            m_keepRunning = true;
        }

        if(m_keepRunning)
        {
            std::cout << "Camera's current velocity while falling down: " << m_cameraVelocity.y << '\n';
            this->fallDown();
        }
    }

    
    std::cout << "Camera height: " << m_cameraPos.y << '\n';

}





void Camera::applyPhysics()
{
    if(M_ENGINE_MODE == INSPECTION_MODE)
    {
        return;
    }

    this->verticalMotion();
    m_collided = false;
    m_collided = this->wasCollided();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//void Camera::changeEngineMode()
//{
//    if(glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_M) == GLFW_PRESS)
//    {
//        M_ENGINE_MODE = (M_ENGINE_MODE == 0) ? 1 : 0;
//    }
//}

float Camera::zoomValue()
{
    return m_zoomValue;
}


bool Camera::keyPressed(GLFWwindow *m_window, const uint16_t KEYTOKEN)
{
    return (glfwGetKey(m_window, KEYTOKEN) == GLFW_PRESS);
}



//this function should only take user input
//will bind up other codes in other structures
void Camera::getKeyboardInput(GLFWwindow* m_window)
{
    using namespace Calculate;

    //renderingInfo::framesPerSecond();

    this->setCameraSpeed();

    //speed up the camera if left shift was pressed
    bool leftShiftPressed = false;
    if(glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        //increase(m_cameraSpeed);
        m_cameraSpeed = m_cameraSpeed * 3.0f;
        leftShiftPressed = true;
    }


//    if(glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
//    {
//        m_jumped = true;
//        m_initialHeight = m_cameraPos.y;
//    }

    //&& !m_collided
    if(keyPressed(m_window, GLFW_KEY_SPACE) && !m_jumped)
    {
        m_jumped = true;
        m_initialHeight = m_cameraPos.y;
    }

    std::cout << "Current Min height: " << m_initialHeight << '\n';

    if(keyPressed(m_window, GLFW_KEY_LEFT_CONTROL) && keyPressed(m_window, GLFW_KEY_R))
    {
        m_cameraPos.y = 0.0f;
    }

//    isLookingAtObject = false;
//    bool shoot = false;
//    if((m_targetPos.x <= m_objectMaxSize.x && m_targetPos.x >= m_objectMinSize.x) &&
//       (m_targetPos.z <= m_objectMaxSize.z && m_targetPos.z >= m_objectMinSize.z) &&
//       (m_targetPos.y <= m_objectMaxSize.y && m_targetPos.y >= m_objectMinSize.y))
//    {
//        isLookingAtObject = true;
//        std::cout << "Camera is looking at Entity!" << '\n';
//    }
//
//    if(isLookingAtObject && glfwGetKey(m_window, GLFW_KEY_O) == GLFW_PRESS)
//    {
//        shoot = true;
//        std::cout << "Shooting!" << '\n';
//    }





    M_ENGINE_MODE = GAME_MODE;



//    if(glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
//    {
//        M_ENGINE_MODE = (M_ENGINE_MODE == GAME_MODE) ? INSPECTION_MODE, m_jumped = false : GAME_MODE;
//    }




    
//    if(glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_KP_ADD) == GLFW_PRESS && m_zoomValue > 5.0f)
//    {
//        m_zoomed = true;
//        //m_zoomValue = 30.0f;
//        m_zoomValue -= 5.0f;
//    }
//    else if(glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && m_zoomValue < 150.0f)
//    {
//        //m_zoomed = false;
//        //m_zoomValue = 45.0f;
//        m_zoomValue += 5.0f;
//    }

//    if(glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
//    {
//        m_zoomValue = 45.0f;
//    }

    std::clog << "Current Field of view of the Camera: " << m_zoomValue << '\n';
    //will add scrolling for this
//    if(m_zoomed)
//    {
//        --m_zoomValue;
//    }


    if(glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS)
    {
        m_crouch = true;
        m_cameraPos.y -= 0.5f;
        if(m_jumped)
        {
            m_crouch = false;
            m_cameraPos.y += 0.5f;
        }
        //motion.decreaseHeight(0.5f);
        if(m_cameraPos.y <= -10.0f)
        {
            m_cameraPos.y = -9.0f;
        }
    }



    //bool collided = false;


//will use this in the main.cpp main Engine loop    
// #define INSPECTION_MODE
// //#define GAME_MODE
// #ifdef GAME_MODE

//     //this->applyPhysics();

// #endif

    m_cameraSpeed = m_cameraSpeed * Calculate::m_rightAngleMovingSpeed;
    std::cout << "Current Camera speed is: " << m_cameraSpeed << '\n';


    //std::thread t1(askForSpeedUp, m_cameraSpeed);
    //t1.join();




    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
//        if(m_targetPos != m_cameraPosWhileCollision)
//        {
//            m_cameraPos.x = m_cameraPos.x + m_cameraSpeed * Calculate::m_directionVector.x * Calculate::m_rightAngleMovingSpeed;
//            m_cameraPos.z = m_cameraPos.z + m_cameraSpeed * Calculate::m_directionVector.z * Calculate::m_rightAngleMovingSpeed;
//        }


        if(!m_collided && M_ENGINE_MODE == GAME_MODE)
        {
            m_cameraPos.x = m_cameraPos.x + m_cameraSpeed * Calculate::m_directionVector.x * Calculate::m_rightAngleMovingSpeed;
            m_cameraPos.z = m_cameraPos.z + m_cameraSpeed * Calculate::m_directionVector.z * Calculate::m_rightAngleMovingSpeed;
        }
        else if(M_ENGINE_MODE == INSPECTION_MODE)
        {
            m_cameraPos = m_cameraPos + m_cameraSpeed * Calculate::m_directionVector * Calculate::m_rightAngleMovingSpeed;
        }

    }
    else if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
//        if(!m_collided && M_ENGINE_MODE == 1)
//        {
            m_cameraPos.x = m_cameraPos.x - m_cameraSpeed * Calculate::m_directionVector.x * Calculate::m_rightAngleMovingSpeed;
            m_cameraPos.z = m_cameraPos.z - m_cameraSpeed * Calculate::m_directionVector.z * Calculate::m_rightAngleMovingSpeed;
//        }
//        else if(M_ENGINE_MODE == 0)
//        {
//            m_cameraPos = m_cameraPos - m_cameraSpeed * Calculate::m_directionVector * Calculate::m_rightAngleMovingSpeed;
//        }
    }
    else if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_cameraPos = m_cameraPos + m_cameraSpeed * glm::normalize(glm::cross(Calculate::m_directionVector, m_cameraUpVector));
    }
    else if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_cameraPos = m_cameraPos - m_cameraSpeed * glm::normalize(glm::cross(Calculate::m_directionVector, m_cameraUpVector));
    }



    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout << "W and A pressed!" << '\n';
        m_cameraPos = m_cameraPos - 1.0f * m_cameraSpeed * glm::normalize(glm::cross(Calculate::m_directionVector, m_cameraUpVector));
    }

    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "W and D pressed!" << '\n';
        m_cameraPos = m_cameraPos + 1.0f * m_cameraSpeed * glm::normalize(glm::cross(Calculate::m_directionVector, m_cameraUpVector));
    }

    if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout << "S and A pressed!" << '\n';
        m_cameraPos = m_cameraPos - 1.0f * m_cameraSpeed * glm::normalize(glm::cross(Calculate::m_directionVector, m_cameraUpVector));
    }

    if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "S and D pressed!" << '\n';
        m_cameraPos = m_cameraPos + 1.0f * m_cameraSpeed * glm::normalize(glm::cross(Calculate::m_directionVector, m_cameraUpVector));
    }


//    if(m_collided)
//    {
//        m_cameraPos = m_cameraPosWhileCollision;
//    }


    //reset the camera speed
    if(leftShiftPressed)
    {
        setCameraSpeed();
    }

}



void Camera::lookAtTarget()
{
    m_targetPos = m_cameraPos + Calculate::m_directionVector;

    LOG('\n');
    LOG("Camera's direction vector: ");
    LOG_GLM(Calculate::m_directionVector);
    LOG('\n');

    LOG("Camera's current Position: ");
    LOG_GLM(m_cameraPos);
    LOG('\n');

    LOG("Camera's target Position: ");
    LOG_GLM(m_targetPos);
    LOG('\n');

    m_view = glm::lookAt(m_cameraPos, m_targetPos, m_cameraUpVector);
}



void Camera::isLookingAtEntity()
{
//    glm::vec3 entityPos = glm::vec3(0.0f, 0.0f, 0.0f);
//    glm::vec3 distanceVec = m_cameraPos - entityPos;

//    if(glm::dot(distanceVec, m_targetPos) == glm::magnitude(distanceVec) * glm::magnitude(m_targetPos))
//    {
//        std::clog << "Camera looking at Entity!" << '\n';
//        isLookingAtObject = true;
//    }

    //glm::vec3 differenceVec = Calculate::m_directionVector - distanceVec;

    //differenceVec = glm::abs(differenceVec);


//    bool shoot = false;
//    if((m_targetPos.x <= m_objectMaxSize.x && m_targetPos.x >= m_objectMinSize.x) &&
//       (m_targetPos.z <= m_objectMaxSize.z && m_targetPos.z >= m_objectMinSize.z) &&
//       (m_targetPos.y <= m_objectMaxSize.y && m_targetPos.y >= m_objectMinSize.y))
//    {
//        isLookingAtObject = true;
//        std::cout << "Camera is looking at Entity!" << '\n';
//    }
//
//    if(isLookingAtObject)


    glm::vec3 entityPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 differenceVec = entityPos - Calculate::m_directionVector;

    if(differenceVec.x <= m_objectMaxSize.x &&
       differenceVec.x >= m_objectMinSize.x &&
       differenceVec.z <= m_objectMaxSize.z &&
       differenceVec.z >= m_objectMinSize.z &&
       differenceVec.y <= m_objectMaxSize.y &&
       differenceVec.y >= m_objectMinSize.y)
    {
        std::cout << "Camera looking at cube!" << '\n';
    }


}



void Camera::update()
{
    //this->getKeyboardInput();
    //this->changeEngineMode();

    this->applyPhysics();
    this->updatePerspective();
    this->viewLocation();
    this->perspectiveLocation();
    this->lookAtTarget();
    //this->isLookingAtEntity();
}


//static function
void Camera::setupMouse(GLFWwindow* window)
{
    glfwSetCursorPosCallback(window, Calculate::mouseInput);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
