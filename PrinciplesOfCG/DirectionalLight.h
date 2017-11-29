#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
private:
    glm::vec3 lightDirection;
public:
    DirectionalLight(int objectId, glm::vec3 intensity, glm::vec3 direction);
    ~DirectionalLight();

    LightStruct getLightInfo() override;
};

