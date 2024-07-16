#include "Projection.hpp"

namespace Synapse
{


glm::mat4 Projection::Perspective(const struct ProjectionData &projectionData)
{
    const float f = glm::cot(glm::radians(projectionData.m_fovDegrees) * 0.5f);

    glm::mat4 resultingPerspectiveMatrix = glm::mat4(0.0f);

    resultingPerspectiveMatrix[0][0] = f/projectionData.m_aspectRatioY;
    resultingPerspectiveMatrix[1][1] = f;
    resultingPerspectiveMatrix[2][2] = projectionData.m_zFar/(projectionData.m_zNear - projectionData.m_zFar);
    resultingPerspectiveMatrix[2][3] = -1.0f;
    resultingPerspectiveMatrix[3][2] = (projectionData.m_zFar * projectionData.m_zNear)/(projectionData.m_zNear - projectionData.m_zFar);

    return resultingPerspectiveMatrix;
}



glm::mat4 Projection::Perspective(const float fovDegrees, const float aspectRatioY, const float zNear, const float zFar)
{
    const float f = glm::cot(glm::radians(fovDegrees) * 0.5f);

    glm::mat4 resultingPerspectiveMatrix = glm::mat4(0.0f);

    resultingPerspectiveMatrix[0][0] = f/aspectRatioY;
    resultingPerspectiveMatrix[1][1] = f;
    resultingPerspectiveMatrix[2][2] = zFar/(zNear - zFar);
    resultingPerspectiveMatrix[2][3] = -1.0f;
    resultingPerspectiveMatrix[3][2] = (zFar * zNear)/(zNear - zFar);

    return resultingPerspectiveMatrix;
}



glm::mat4 Projection::Orthographic(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
{
    glm::mat4 resultingOrthographicMatrix = glm::mat4(0.0f);
    return resultingOrthographicMatrix;
}






//    static glm::mat4 Perspective(float fieldOfViewYDegrees, float aspectRatioY, float zNear, float zFar)
//    {
//        const float f = glm::cot(glm::radians(fieldOfViewYDegrees) * 0.5f);
//
////    glm::mat4 resultingPerspectiveMatrix = glm::mat4(0.0f);
//
////    resultingPerspectiveMatrix[0][0] = f/aspectRatioY;
////    resultingPerspectiveMatrix[1][1] = f;
////    resultingPerspectiveMatrix[2][2] = zFar/(zNear - zFar);
////    resultingPerspectiveMatrix[2][3] = -1.0f;
////    resultingPerspectiveMatrix[3][2] = (zFar * zNear)/(zNear - zFar);
////
////    return resultingPerspectiveMatrix;
//
//        return glm::mat4(f/aspectRatioY, 0.0f, 0.0f, 0.0f,
//                         0.0f, f, 0.0f, 0.0f,
//                         0.0f, 0.0f, zFar/(zNear - zFar), -1.0f,
//                         0.0f, 0.0f, (zFar * zNear)/(zNear - zFar), 0.0f);
//    }
//


//    m_f = glm::cot(glm::radians(m_fovDegrees) * 0.5f);
//    m_projection[0][0] = m_f/m_aspectRatioY;
//    m_projection[1][1] = m_f;



}