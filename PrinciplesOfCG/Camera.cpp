#include "stdafx.h"
#include "Camera.h"


Camera::Camera(int id, glm::vec3 worldPosition, glm::vec3 target) : ObjectWithTarget(id, worldPosition, target)
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
    return glm::lookAt(this->worldPosition, this->worldPosition + this->target, this->upVector);
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
        this->worldPosition += 2.0f * (CAMERA_SPEED * this->upVector);
        break;
    case Down:
        this->worldPosition += 2.0f * (-CAMERA_SPEED * this->upVector);
        break;
    case Left: 
    {
        glm::vec3 strafeDirection = glm::cross(this->target, this->upVector);
        this->worldPosition += -CAMERA_SPEED * strafeDirection;
        break;
    }
    case Right:
    {
        glm::vec3 strafeDirection = glm::cross(this->target, this->upVector);
        this->worldPosition += CAMERA_SPEED * strafeDirection;
        break;
    }
    case Forward:
        this->worldPosition += CAMERA_SPEED * this->target;
        break;
    case Backward:
        this->worldPosition += -CAMERA_SPEED * this->target;
        break;
    }

    //printf("Current camera position: [x: %f; y: %f, z: %f]\n",
    //    this->worldPosition.x, this->worldPosition.y, this->worldPosition.z);

    if (direction != None)
    {
        notifyObservers(this->getViewMatrix(), this->getProjectionMatrix(), this->worldPosition);
    }
}

//void Camera::moveCameraAndTarget(Direction direction)
//{
//    switch (direction)
//    {
//    case Up:
//        this->worldPosition += glm::vec3(0.0f, 0.5f, 0.0f);
//        this->target += glm::vec3(0.0f, 0.5f, 0.0f);
//        break;
//    case Down:
//        this->worldPosition += glm::vec3(0.0f, -0.5f, 0.0f);
//        this->target += glm::vec3(0.0f, -0.5f, 0.0f);;
//        break;
//    case Left:
//        this->worldPosition += glm::vec3(-0.5f, 0.0f, 0.0f);
//        this->target += glm::vec3(-0.5f, 0.0f, 0.0f);
//        break;
//    case Right:
//        this->worldPosition += glm::vec3(0.5f, 0.0f, 0.0f);
//        this->target += glm::vec3(0.5f, 0.0f, 0.0f);
//        break;
//    case Forward:
//        this->worldPosition += glm::vec3(0.0f, 0.0f, -0.5f);
//        this->target += glm::vec3(0.0f, 0.0f, -0.5f);
//        break;
//    case Backward:
//        this->worldPosition += glm::vec3(0.0f, 0.0f, 0.5f);
//        this->target += glm::vec3(0.0f, 0.0f, 0.5f);
//        break;
//    }
//
//    printf("Current camera position: [x: %f; y: %f, z: %f]\n",
//        this->worldPosition.x, this->worldPosition.y, this->worldPosition.z);
//    printf("Current eye position: [x: %f; y: %f, z: %f]\n",
//        this->target.x, this->target.y, this->target.z);
//
//    if (direction != None)
//    {
//        notifyObservers(getViewMatrix(), getProjectionMatrix());
//    }
//}

void Camera::mouseUpdate(const glm::vec2 & mousePosition)
{
    glm::vec2 mouseDelta = mousePosition - oldMousePosition;
    
    if (glm::length(mouseDelta) > 50.0f)
    {
        oldMousePosition = mousePosition;
        return;                                                                      
    }

    glm::vec3 toRotateAround = glm::cross(this->target, this->upVector);
    glm::mat4 rotator = glm::rotate(mouseDelta.x / 500.0f, this->upVector) * glm::rotate(mouseDelta.y/500.0f, toRotateAround);
    this->target = glm::mat3(rotator) * this->target;


    oldMousePosition = mousePosition;
    notifyObservers(this->getViewMatrix(), this->getProjectionMatrix(), this->worldPosition);
}

void Camera::resetCamera()
{
    this->worldPosition = this->backupWorldPosition;
    this->target = this->backupTargetPosition;
    notifyObservers(this->getViewMatrix(), this->getProjectionMatrix(), this->worldPosition);
}

void Camera::registerObserver(CameraObserver & observer)
{
    CameraSubject::registerObserver(observer);
    notifyObservers(this->getViewMatrix(), this->getProjectionMatrix(), this->worldPosition);
}

void Camera::forceUpdate()
{
    this->notifyObservers(getViewMatrix(), getProjectionMatrix(), this->worldPosition);
}
