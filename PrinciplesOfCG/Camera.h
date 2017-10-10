#pragma once

#include "ObjectWithFocus.h"

class Camera : public ObjectWithFocus
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
};

