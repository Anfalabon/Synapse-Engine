#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "scene/editor/Camera.hpp"
#include "physics/PhysicsEngine.hpp"
#include "scene/Entities.hpp"
#include "renderer/shader/Shader.hpp"
#include "math/Projection.hpp"
//#include "../events/MouseEvents.hpp"



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
    : m_physics(new Physics()),
      m_projectionData({45.0f, 1920.0f / 1080.0f, 0.1f, 2000.0f}),
      m_cameraProjectionType(cameraProjectionType),
      m_cameraMode(CAMERA_MODES::INSPECTION_MODE),
      m_cameraIndexID(cameraIndexID)
    {
        switch(cameraProjectionType)
        {
            case PROJECTION_TYPES::PERSPECTIVE :  m_projection = Projection::Perspective(m_projectionData); break;
            case PROJECTION_TYPES::ORTHOGRAPHIC :  m_projection = Projection::Orthographic(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f); break;
        }
    }

    ~SceneCamera() = default;

    //void SetViewPort();
    void SetCameraMode(const CAMERA_MODES &cameraMode);
    void GetKeyboardInput(GLFWwindow *window, const float deltaTime);
    void Update(GLFWwindow *window, Shader &shader, const float deltaTime);    //const std::vector<Synapse::RenderableObject*> &renderableObjects,
    void SetupMouse(GLFWwindow *window);

    __ALWAYS__INLINE__ std::size_t GetIndex() const {return m_cameraIndexID;}
    __ALWAYS__INLINE__ glm::vec3   GetPos() const {return m_position;}
    __ALWAYS__INLINE__ glm::vec3   GetTargetPos() const {return m_targetPos;}
    __ALWAYS__INLINE__ glm::vec3   GetFrontVector() const {return m_frontVector;}    //Cursor::g_cursorsData[m_cameraIndexID].m_frontVector;
    __ALWAYS__INLINE__ glm::vec3   GetTranslatedFrontVector() const
    {
        glm::vec3 frontVector = m_frontVector;
        frontVector += m_position;
        return frontVector;
    }

private:

    void CalculateFrontVector(float yaw, float pitch);
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
    void UpdateSpeed(const float deltaTime){}   //for now ResetSpeed() and IncreaseSpeed() will do the job
    bool IncreaseSpeed(GLFWwindow *window);
    void ResetSpeed(const float deltaTime);
    void EnableJumpingInput(GLFWwindow *window);
    void ApplyZoomEffect(GLFWwindow *window);
    void ApplyMovement(GLFWwindow *window);
    void ApplyMultipleDirectionMovement(GLFWwindow *window);
    void SetCursorData();
    void GetCursorData();

private:

    glm::vec3 m_position    = glm::vec3(3.0f, 0.0f, 3.0f);
    glm::vec3 m_velocity    = glm::vec3(0.0f, 0.774f, 0.0f);

    glm::vec3 m_targetPos   = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_upVector    = glm::vec3(0.0f, 1.0f, 0.0f);   //camera up vector is arbitary
    glm::vec3 m_frontVector = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 m_projection  = glm::mat4(0.0f);
    glm::mat4 m_view        = glm::mat4(1.0f);


    float                 m_speedCoefficient;
    Physics              *m_physics;
    bool                  m_changedFov = false;
    struct ProjectionData m_projectionData;


    PROJECTION_TYPES      m_cameraProjectionType;
    CAMERA_MODES          m_cameraMode;
    const std::size_t     m_cameraIndexID = 0;  //this is initialized here because of the default constructor


    //GLFWwindow *window;
    //MouseEvents mouseEvents;
    //struct CursorData cursor;

};



}