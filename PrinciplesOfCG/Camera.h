#pragma once

#include "ObjectWithFocus.h"
#include "Subject.h"

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

class Camera : public ObjectWithFocus, public Subject
{
private:
    glm::vec3 upVector;
    float fieldOfView;
    float aspectRatio;
    float zNear;
    float zFar;

public:
    Camera(int, glm::vec3, glm::vec3);
    ~Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setPerspective(float, float, float, float);

    void moveCamera(Direction);
    
};

