#pragma once
#include <glm\glm.hpp>
class LightObserver
{
public:
    virtual void lightNotify(glm::vec3 worldPosition, glm::vec3 lightIntensity, glm::vec3 ambient, float lightPower) = 0;
};

