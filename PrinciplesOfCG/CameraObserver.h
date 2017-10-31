#pragma once
#include <glm\glm.hpp>

class CameraObserver
{
public:
    virtual void cameraNotify(glm::mat4, glm::mat4, glm::vec3) = 0;
};

