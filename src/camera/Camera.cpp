#include "Camera.hpp"
#include "camera/Cursor.hpp"   //include 'Cursor.hpp' after 'Camera.hpp' cause cursor includes GLFW and glm followed by and camera's inclusion of glad
#include "debug/LOG.hpp"

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <iostream>


namespace Synapse
{


//this should be inside the Engine class
void Camera::SetCameraMode(const CAMERA_MODES &cameraMode)
{
    m_cameraMode = cameraMode;
}



void Camera::CalculateFrontVector(float yaw, float pitch)
{
    glm::vec3 frontVector;  //using this is maybe waste of memory when everytime mouse is moved
    frontVector.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    frontVector.y = glm::sin(glm::radians(pitch));
    frontVector.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    m_frontVector = glm::normalize(frontVector);
}



void Camera::AddShader(const Shader &shader)
{
    m_shader = shader;
}


void Camera::UpdateViewMatrix()
{
    //m_targetPos = m_physics->m_pos + Cursor::g_cursorsData[M_CAMERA_INDEX_ID].m_frontVector;
    m_targetPos = m_position + m_frontVector;

    DEBUG::__LOG__MANAGER__::LOG('\n');
    //this is the vector which represents where the camera is pointing at
    DEBUG::__LOG__MANAGER__::LOG("Camera's direction vector: ");
    DEBUG::__LOG__MANAGER__::GLM_LOG(Cursor::g_cursorsData[m_cameraIndexID].m_frontVector);
    DEBUG::__LOG__MANAGER__::LOG('\n');

    DEBUG::__LOG__MANAGER__::LOG("Camera's current Position: ");
    DEBUG::__LOG__MANAGER__::GLM_LOG(m_position);
    DEBUG::__LOG__MANAGER__::LOG('\n');

    DEBUG::__LOG__MANAGER__::LOG("Camera's target Position: ");
    DEBUG::__LOG__MANAGER__::GLM_LOG(m_targetPos);
    DEBUG::__LOG__MANAGER__::LOG('\n');


    m_view = glm::lookAt(m_position, m_targetPos, m_upVector);

    //this is for slow speed when the camera is pointing towards up-most or down-most
//    glm::vec3 m_cameraWorldUp = m_cameraUpVector;
//    glm::vec3 m_cameraRightVector = glm::normalize(glm::cross(Calculate::m_frontVector, m_cameraWorldUp));
//    m_cameraUpVector = glm::normalize(glm::cross(m_cameraRightVector, Calculate::m_frontVector));

#if 0
    glm::mat4 inverseViewMatrix = glm::inverse(m_view);
    glm::vec3 cameraPos(inverseViewMatrix[3]);

    if(cameraPos == m_physics->m_pos)
    {
        DEBUG("They are equal!");
        //std::cin.get();
    }
#endif


}





void Camera::UpdateProjectionMatrix()
{
    if(m_changedFov)
    {
        m_projection = Projection::Perspective(m_projectionData);
    }

    //m_projection = glm::perspective(glm::radians(m_fovDegrees), 1920.0f / 1080.0f, nearFustrum, farFustrum);
    //m_projection = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, nearFustrum, farFustrum);
}



void Camera::ResetSpeed(const float deltaTime)
{
    const float cameraSpeedConstant = 20.0f;
    m_speedCoefficient = cameraSpeedConstant * deltaTime;
}



bool Camera::IncreaseSpeed(GLFWwindow *m_window)
{
    if(glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        m_speedCoefficient *= 3.0f;
        return true;
    }
    return false;
}





void Camera::ApplyZoomEffect(GLFWwindow *m_window)
{
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS &&
        glfwGetKey(m_window, GLFW_KEY_KP_ADD) == GLFW_PRESS && m_projectionData.m_fovDegrees > 5.0f)
    {
        //m_zoomValue -= 5.0f;
        m_projectionData.m_fovDegrees -= 5.0f;
        m_changedFov = true;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS &&
             glfwGetKey(m_window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && m_projectionData.m_fovDegrees < 150.0f)
    {
        //m_zoomValue += 5.0f;
        m_projectionData.m_fovDegrees += 5.0f;
        m_changedFov = true;
    }

    if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        //m_zoomValue = 45.0f;
        m_projectionData.m_fovDegrees = 45.0f;
        m_changedFov = true;
    }

    std::clog << "Current Field of view of the Camera: " << m_projectionData.m_fovDegrees << '\n';
    //will add scrolling for this
#ifdef ZOOM_SCROLLING
    if(m_projectionData.m_changedFov)
    {
        --m_projectionData.m_fovDegrees;
        //++m_fovDegrees;
    }
#endif


}



void Camera::ApplyMovement(GLFWwindow *m_window)
{

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        //in game mode it can freely move in the ground plane only(x, z plane) but It can't move vertically.
        //and in inspection mode it can move in anywhere freely.
        if (m_cameraMode == CAMERA_MODES::GAME_MODE)
        {
            //if the camera collided with any object then it can't move further.
            //doing action on collision detection like this has a lot of problems
            //wil fix it.
            if (!m_physics->m_collided)
            {
                m_position.x += m_speedCoefficient * m_frontVector.x;
                m_position.z += m_speedCoefficient * m_frontVector.z;
            }
        }
        else if (m_cameraMode == CAMERA_MODES::INSPECTION_MODE)
        {
            //Cursor::g_cursorsData[M_CAMERA_INDEX_ID].m_frontVector *= m_physics->m_speedCoefficient;
            //m_physics->m_pos = m_physics->m_pos + Cursor::g_cursorsData[M_CAMERA_INDEX_ID].m_frontVector;
            m_position += m_speedCoefficient * m_frontVector;
        }

    }
    else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_position.x -= m_speedCoefficient * m_frontVector.x;
        m_position.z -= m_speedCoefficient * m_frontVector.z;
    }
    else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_position += m_speedCoefficient * glm::normalize(glm::cross(m_frontVector, m_upVector));
    }
    else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_position -= m_speedCoefficient * glm::normalize(glm::cross(m_frontVector, m_upVector));
    }



    //multiple direction movement


    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout << "W and A pressed!" << '\n';
        m_position -= m_speedCoefficient * glm::normalize(glm::cross(m_frontVector, m_upVector));
    }

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "W and D pressed!" << '\n';
        m_position += m_speedCoefficient * glm::normalize(glm::cross(m_frontVector, m_upVector));
    }

    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout << "S and A pressed!" << '\n';
        m_position -= m_speedCoefficient * glm::normalize(glm::cross(m_frontVector, m_upVector));
    }

    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "S and D pressed!" << '\n';
        m_position += m_speedCoefficient * glm::normalize(glm::cross(m_frontVector, m_upVector));
    }


}





void Camera::EnableJumpingInput(GLFWwindow *m_window)
{
    //&& !m_collided
    if(glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS &&
       !m_physics->m_jumped &&
       m_cameraIndexID == CAMERA_MODES::GAME_MODE)
    {
        m_physics->m_jumped = true;
        m_physics->m_initialHeight = m_position.y;
    }
}





//this function should only take user input
//will bind up other codes in other structures
void Camera::GetKeyboardInput(GLFWwindow *m_window, const float deltaTime)
{

    bool wasSpeedIncreased = this->IncreaseSpeed(m_window);
    this->EnableJumpingInput(m_window);
    this->ApplyZoomEffect(m_window);
    this->ApplyMovement(m_window);

    //reset the camera speed
    if(wasSpeedIncreased)
    {
        this->ResetSpeed(deltaTime);
    }

    //this->ChangeCameraMode(m_window);

}








void Camera::Update(const std::vector<Synapse::RenderableObject*> &renderableObjects, const float deltaTime)
{
    //this->GetKeyboardInput();
    //this->UpdateSpeed(deltaTime);

    //this->ChangeCameraMode();

    Cursor::g_cameraIndex = m_cameraIndexID;    //this is used to switch between cameras


    this->SetCameraMode(CAMERA_MODES::INSPECTION_MODE);
    if (m_cameraMode == CAMERA_MODES::GAME_MODE)
    {
        m_physics->m_pos = m_position;
        m_physics->m_velocity = m_velocity;

        m_physics->Apply(renderableObjects); //this doesn't check Camera mode and just simply applies physics regarding of cameras actual mode

        m_position = m_physics->m_pos;
        m_velocity = m_physics->m_velocity;
    }

    this->CalculateFrontVector(Cursor::g_cursorsData[m_cameraIndexID].m_yaw, Cursor::g_cursorsData[m_cameraIndexID].m_pitch);
    m_shader.SendMatrix4ToGPU("view", m_view);
    m_shader.SendMatrix4ToGPU("projection", m_projection);
    this->UpdateViewMatrix();
    this->UpdateProjectionMatrix();
    //this->LookAtTarget();
}



void Camera::SetCursorData()
{

}


void Camera::GetCursorData()
{
    //return Cursor::g_cursorsData[m_cameraIndexID];
}



//non-static function
void Camera::SetupMouse(GLFWwindow *window)
{
    if(m_cameraIndexID < 0)
    {
        return;
    }

    std::cout << m_cameraIndexID << '\n';

    Cursor::g_cursorsData.push_back(Cursor::CursorData());
    glfwSetCursorPosCallback(window, Cursor::mouseInput);  //MouseEvents::mouseInput
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}



}