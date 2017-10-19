#pragma once

#include "ObjectWithTarget.h"
#include "CameraSubject.h"

enum Direction
{
    Up,
    Down,
    Left,
    Right,
    Forward,
    Backward,
    None
};

class Camera : public ObjectWithTarget, public CameraSubject
{
private:
    glm::vec3 upVector;
    float fieldOfView;
    float aspectRatio;
    float zNear;
    float zFar;

    glm::vec3 backupWorldPosition, backupTargetPosition;

public:
    Camera(int, glm::vec3, glm::vec3);
    ~Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setPerspective(float, float, float, float);

    void moveCamera(Direction);
    void moveCameraAndEye(Direction);
    void lookAround(double, double);
    void resetCamera();

    void registerObserver(CameraObserver&) override;
};

