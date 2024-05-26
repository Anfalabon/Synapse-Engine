#pragma once

#include "../physics/PhysicsEngine.hpp"

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>


class Camera
{
public:

    enum CAMERA_MODES
    {
        GAME_MODE = 0x0,
        INSPECTION_MODE = 0x1,
    };

    explicit Camera()
        : m_deltaTime(0.0f),
          m_lastFrame(0.0f),
          M_CAMERA_MODE(CAMERA_MODES::GAME_MODE)
          {
              motion.calculateDeltaTime();
          }

    ~Camera() = default;


    void setCameraMode(CAMERA_MODES M);
    void changeCameraMode(){} //will declare it later
    void addShaderProgramID(GLuint shaderProgramID);
    void getPerspectiveMatrixLocation();
    void getViewMatrixLocation();
    void updatePerspective();
    void updateView(glm::mat4 &view);
    void lookAtTarget();   //this is the overloaded function of glm::lookAt(). So the it will return : return glm::lookAt(cameraPos, targetPos, upVecPos)
    void isLookingAtEntity();
    void updateCameraSpeed();
    void setCurrentObjectInfo(const glm::vec3 &maxObjectRange, const glm::vec3 &minObjectRange);


    //this is the physics part
    //will separate this physics part and generalize meaning the physics will work not only for the Camera but also for other Entities
    //for some general physics stuffs will keep them in the Physics Engine class
    bool wasCollided();
    void initVelocity(const glm::vec3 &velocity); //throw with initial velocity
    void fallDown();
    void jump();
    void applyVerticalMotions();

    void applyPhysics();



    float zoomValue();
    bool keyPressed(GLFWwindow *m_window, const uint16_t KEYTOKEN);
    void getKeyboardInput(GLFWwindow* window);


    void update();

//    static void calculateDirectionVector();    //this is equavalent to calculating the cameraFront vector
    static void setupMouse(GLFWwindow* window);


private:


    //may initialize these vectors and the matix in the initializer list
    //glm::vec3 m_directionVector = glm::vec3(0.0f, 0.0f, -1.0f);

    struct PhysicsEngine motion;

    glm::vec3 m_cameraPos = glm::vec3(3.0f, 0.0f, 3.0f);
    glm::vec3 m_cameraPosWhileCollision = glm::vec3(3.0f, 0.0f, 3.0f);
    glm::vec3 m_targetPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_cameraUpVector = glm::vec3(0.0f, 1.0f, 0.0f);   //camera up vector is arbitary

    glm::vec3 m_cameraVelocity = glm::vec3(0.0f,  0.774f, 0.0f);


    //Physics motion(m_cameraPos, m_cameraVelocity);

    glm::mat4 m_perspective = glm::mat4(1.0f);
    glm::mat4 m_view = glm::mat4(1.0f);

    glm::vec3 m_objectMaxSize = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_objectMinSize = glm::vec3(0.0f, 0.0f, 0.0f);



    //bool m_jumped = false;
    bool m_isAtTheRoof = false;    //check if the camera is at the top of the current object it's interecting with
    bool m_keepRunning = false;
    bool m_collided = false;

    float m_initialHeight = 0.0f;    //current initial height before jumping


    // const float m_jumpMaxHeight;
    // const float m_jumpSpeed;
    float m_currentObjectHeight = 0.0f;


    float m_timeElapsed = 0.0f;
    //float alpha = 0.0f;   // timeElapsedSinceJump
    //float beta = 0.455;   // timeElapsedSinceFall

    float m_cameraSpeed;
    float m_deltaTime;
    float m_lastFrame;

    bool  m_zoomed = false;
    float m_zoomValue = 45.0f;  //this is basically the Field of view of the camera

    bool  m_crouch = false;

    //GLuint m_shaderProgramID;
    std::vector<GLuint> m_shaderProgramIDs;

    bool m_firstMouse = true;

    bool isLookingAtObject = false;

    bool m_addedNewEntityShader = false;


    const CAMERA_MODES M_CAMERA_MODE;

};
