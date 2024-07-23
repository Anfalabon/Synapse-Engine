#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "scene/editor/Camera.hpp"
#include "renderer/shader/Shader.hpp"
#include "math/Projection.hpp"
//#include "../events/MouseEvents.hpp"

//#include "physics/PhysicsEngine.hpp"
//#include "scene/Entities.hpp"


namespace Synapse
{



class SceneCamera : public Camera
{
public:

    enum PROJECTION_TYPES
    {
        PERSPECTIVE = 0x0,
        ORTHOGRAPHIC = 0X1
    };

    enum CAMERA_MODES
    {
        GAME_MODE = 0x0,
        INSPECTION_MODE = 0x1
    };

    SceneCamera() = default;

    explicit SceneCamera(const std::size_t &cameraIndexID = 0, const PROJECTION_TYPES &cameraProjectionType = PROJECTION_TYPES::PERSPECTIVE)
    : m_projectionData({45.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f}),
      m_cameraProjectionType(cameraProjectionType),
      m_cameraMode(CAMERA_MODES::INSPECTION_MODE),
      m_cameraIndexID(cameraIndexID)
    {
        switch(cameraProjectionType)
        {
            case PROJECTION_TYPES::PERSPECTIVE  :  m_projection = Projection::Perspective(45.0f, 1920.0f / 1080.0f, 0.1f, 2000.0f); break;
            case PROJECTION_TYPES::ORTHOGRAPHIC :  m_projection = Projection::Orthographic(0.0f, 1920.0f, 0.0f, 1080.0f, 0.1f, 1000.0f); break;
        }
    }

    ~SceneCamera() = default;

    //void SetViewPort();
    void SetCameraMode(const CAMERA_MODES &cameraMode);
    void GetKeyboardInput(GLFWwindow *window, const float deltaTime);
    void Update(GLFWwindow *window, Shader &shader, const float deltaTime);    //const std::vector<Synapse::RenderableObject*> &renderableObjects,
    void SetupMouse(GLFWwindow *window);


    __ALWAYS__INLINE__ void SetPos(const glm::vec3 &pos){m_position = pos;}
    __ALWAYS__INLINE__ void SetVelocity(const glm::vec3 &velocity){m_velocity = velocity;}

    __ALWAYS__INLINE__ std::size_t GetIndex() const {return m_cameraIndexID;}
    __ALWAYS__INLINE__ glm::vec3   GetPos() const {return m_position;}
    __ALWAYS__INLINE__ glm::vec3   GetVelocity() const {return m_velocity;}
    __ALWAYS__INLINE__ glm::vec3   GetTargetPos() const {return m_targetPos;}
    __ALWAYS__INLINE__ glm::vec3   GetFrontVector() const {return m_frontVector;}    //Cursor::g_cursorsData[m_cameraIndexID].m_frontVector;
    __ALWAYS__INLINE__ glm::mat4   GetViewMatrix() const {return m_view;}
    __ALWAYS__INLINE__ glm::mat4   GetProjectionMatrix() const {return m_projection;}
    __ALWAYS__INLINE__ float       GetYaw(){return m_yaw;}
    __ALWAYS__INLINE__ float       GetPitch(){return m_pitch;}

    __ALWAYS__INLINE__ glm::vec3   GetTranslatedFrontVector() const
    {
        glm::vec3 frontVector = m_frontVector;
        frontVector += m_position;
        return frontVector;
    }

    __ALWAYS__INLINE__ glm::vec3   GetRightVector() const
    {
        return glm::normalize(glm::cross(m_frontVector, m_upVector));
        //return glm::vec3(m_view[0][0], m_view[1][0], m_view[2][0]);
        //return m_rightVector;
    }

    __ALWAYS__INLINE__ glm::vec3   GetLeftVector() const
    {
        return (-1.0f)*this->GetRightVector();
        //return (-1.0f)*glm::vec3(m_view[0][0], m_view[1][0], m_view[2][0]);
        //return m_leftVector;
    }

private:

    void CalculateFrontVector(float yaw, float pitch);
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
    void UpdateVelocity(const float deltaTime){}   //for now ResetSpeed() and IncreaseSpeed() will do the job
    bool IncreaseVelocity(GLFWwindow *window);
    void ResetVelocity(const float deltaTime);
    void ApplyZoomEffect(GLFWwindow *window);
    void ApplyMovement(GLFWwindow *window, const float deltaTime);
    void ApplyMultipleDirectionMovement(GLFWwindow *window, const float deltaTime);
    void SetCursorData();
    void GetCursorData();

private:

    //Tensor Values
    glm::vec3 m_position    = glm::vec3(3.0f, 0.0f, 3.0f);
    glm::vec3 m_velocity    = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 m_targetPos   = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_upVector    = glm::vec3(0.0f, 1.0f, 0.0f);   //camera up vector is arbitary when initializing
    glm::vec3 m_frontVector = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_rigthVector = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 m_projection  = glm::mat4(0.0f);
    glm::mat4 m_view        = glm::mat4(1.0f);

private:

    float                 m_yaw = 0.0f;
    float                 m_pitch = 0.0f;
    bool                  m_changedFov = false;
    struct ProjectionData m_projectionData;

    PROJECTION_TYPES      m_cameraProjectionType;
    CAMERA_MODES          m_cameraMode;
    const std::size_t     m_cameraIndexID = 0;  //this is initialized here because of the default constructor

private:

    //data's which might be used in the future

    //GLFWwindow *window;
    //MouseEvents mouseEvents;
    //struct CursorData cursor;

};



}