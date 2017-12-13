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
    const float CAMERA_SPEED = 0.05f;
    glm::vec2 oldMousePosition;

public:
    Camera(int, glm::vec3 worldPosition, glm::vec3 target);
    ~Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setPerspective(float, float, float, float);

    void moveCamera(Direction);
    //void moveCameraAndTarget(Direction);
    void mouseUpdate(const glm::vec2& mousePosition);
    void resetCamera();

    void registerObserver(CameraObserver&) override;
    void forceUpdate();
};

