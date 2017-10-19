#pragma once
#include "Light.h"
class PointLight : public Light
{
private:
    

    glm::vec3 ambient;
public:
    PointLight();
    PointLight(int objectId, glm::vec3 worldPosition, glm::vec3 lightIntensity, glm::vec3 ambient, float lightPower);
    ~PointLight();

    glm::vec3 getAmbient() const;
};

