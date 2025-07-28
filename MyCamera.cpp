#include "MyCamera.h"



MyCamera::MyCamera(float fovDegrees, float aspectRatio, float nearPlane, float farPlane)
    : _fov(fovDegrees), _aspect(aspectRatio), _near(nearPlane), _far(farPlane)
{
    UpdateCameraVectors();
}

void MyCamera::SetPosition(const glm::vec3& position)
{
    _position = position;
    UpdateCameraVectors();
}

void MyCamera::SetYawPitch(float yawDegrees, float pitchDegrees)
{
    _yaw = yawDegrees;
    _pitch = glm::clamp(pitchDegrees, -89.0f, 89.0f);
    UpdateCameraVectors();
}

glm::mat4 MyCamera::GetViewMatrix() const
{
    return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 MyCamera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(_fov), _aspect, _near, _far);
}

void MyCamera::UpdateCameraVectors()
{
    //alculate the new Front vector.
    glm::vec3 front;

    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    //Re-calculate the Right and Up vector
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}
