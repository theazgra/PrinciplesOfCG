#include "stdafx.h"
#include "Camera.h"


Camera::Camera(int id, glm::vec3 worldPosition, glm::vec3 poi) : ObjectWithFocus(id, worldPosition, poi)
{
    this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    this->fieldOfView = glm::radians(45.0f);
    this->aspectRatio = 4.0f / 3.0f;
    this->zNear = 0.1f;
    this->zFar = 100.0f;
}


Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(this->worldPosition, this->target, this->upVector);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(this->fieldOfView, this->aspectRatio, this->zNear, this->zFar);
}

void Camera::setPerspective(float degrees, float aspectRatio, float zNear, float zFar)
{
    this->fieldOfView = glm::radians(degrees);
    this->aspectRatio = aspectRatio;
    this->zNear = zNear;
    this->zFar = zFar;
}
