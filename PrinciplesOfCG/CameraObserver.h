#pragma once
#include <glm\glm.hpp>

class CameraObserver
{
public:
    //CameraObserver();
    //~CameraObserver();

    virtual void notify(glm::mat4, glm::mat4) = 0;
};

