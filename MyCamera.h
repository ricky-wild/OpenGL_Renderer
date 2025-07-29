

#pragma once
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MyCamera
{
    public:

        MyCamera(float fovDegrees, float aspectRatio, float nearPlane, float farPlane);

        glm::mat4 GetViewMatrix() const; //based on position & orientation

        glm::mat4 GetProjectionMatrix() const; //perspective

        // Position and orientation
        void SetPosition(const glm::vec3& position);
        void SetYawPitch(float yawDegrees, float pitchDegrees);

        glm::vec3 GetPosition() const { return _position; };

    private:

        glm::vec3 _position = glm::vec3(0.0f, 0.0f, 3.0f);
        float _yaw = -90.0f;   
        float _pitch = 0.0f;   

        float _fov;
        float _aspect;
        float _near;
        float _far;

        glm::vec3 _front;   
        glm::vec3 _up;
        glm::vec3 _right;
        glm::vec3 _worldUp = glm::vec3(0, 1, 0);

        void UpdateCameraVectors();
};