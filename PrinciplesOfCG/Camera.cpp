#include "stdafx.h"
#include "Camera.h"




Camera::Camera(int id, glm::vec3 worldPosition, glm::vec3 poi) : ObjectWithFocus(id, worldPosition, poi)
{
    this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    this->fieldOfView = glm::radians(45.0f);
    this->aspectRatio = 4.0f / 3.0f;
    this->zNear = 0.1f;
    this->zFar = 100.0f;

    this->backupWorldPosition = this->worldPosition;
    this->backupTargetPosition = this->target;
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



void Camera::moveCamera(Direction direction)
{
    switch (direction)
    {
    case Up:
        this->worldPosition += glm::vec3(0.0f, 0.5f, 0.0f);
        break;
    case Down:
        this->worldPosition += glm::vec3(0.0f, -0.5f, 0.0f);;
        break;
    case Left:
        this->worldPosition += glm::vec3(-0.5f, 0.0f, 0.0f);
        break;
    case Right:
        this->worldPosition += glm::vec3(0.5f, 0.0f, 0.0f);
        break;
    case Forward:
        this->worldPosition += glm::vec3(0.0f, 0.0f, -0.5f);
        break;
    case Backward:
        this->worldPosition += glm::vec3(0.0f, 0.0f, 0.5f);
        break;
    }

    printf("Current camera position: [x: %f; y: %f, z: %f]\n",
        this->worldPosition.x, this->worldPosition.y, this->worldPosition.z);

    if (direction != None)
    {
        notifyObservers();
    }
}


void Camera::moveCameraAndEye(Direction direction)
{
    switch (direction)
    {
    case Up:
        this->worldPosition += glm::vec3(0.0f, 0.5f, 0.0f);
        this->target += glm::vec3(0.0f, 0.5f, 0.0f);
        break;
    case Down:
        this->worldPosition += glm::vec3(0.0f, -0.5f, 0.0f);
        this->target += glm::vec3(0.0f, -0.5f, 0.0f);;
        break;
    case Left:
        this->worldPosition += glm::vec3(-0.5f, 0.0f, 0.0f);
        this->target += glm::vec3(-0.5f, 0.0f, 0.0f);
        break;
    case Right:
        this->worldPosition += glm::vec3(0.5f, 0.0f, 0.0f);
        this->target += glm::vec3(0.5f, 0.0f, 0.0f);
        break;
    case Forward:
        this->worldPosition += glm::vec3(0.0f, 0.0f, -0.5f);
        this->target += glm::vec3(0.0f, 0.0f, -0.5f);
        break;
    case Backward:
        this->worldPosition += glm::vec3(0.0f, 0.0f, 0.5f);
        this->target += glm::vec3(0.0f, 0.0f, 0.5f);
        break;
    }

    printf("Current camera position: [x: %f; y: %f, z: %f]\n",
        this->worldPosition.x, this->worldPosition.y, this->worldPosition.z);
    printf("Current eye position: [x: %f; y: %f, z: %f]\n",
        this->target.x, this->target.y, this->target.z);

    if (direction != None)
    {
        notifyObservers();
    }
}

void Camera::lookAround(double deltaX, double deltaY)
{
    printf("DeltaX: %f; DeltaY: %f\n", deltaX, deltaY);
    printf("Pre change eye position: [x: %f; y: %f, z: %f]\n", this->target.x, this->target.y, this->target.z);
    this->target.x += float(glm::cos(deltaX));
    this->target.z += float(glm::sin(deltaX));
    this->target.y += float(glm::sin(deltaY));
    printf("Post change eye position: [x: %f; y: %f, z: %f]\n", this->target.x, this->target.y, this->target.z);


    notifyObservers();
}

void Camera::resetCamera()
{
    this->worldPosition = this->backupWorldPosition;
    this->target = this->backupTargetPosition;
}
