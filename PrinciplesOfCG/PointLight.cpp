#include "stdafx.h"
#include "PointLight.h"

PointLight::PointLight()
{
}

PointLight::PointLight(int objectId, glm::vec3 worldPosition, glm::vec3 intensity, glm::vec3 ambient, float power)
    : Light(objectId, worldPosition, intensity, power)
{
    this->ambient = ambient;
}

PointLight::~PointLight()
{
}

glm::vec3 PointLight::getAmbient() const
{
    return this->ambient;
}

void PointLight::setAmbient(glm::vec3 ambient)
{
    this->ambient = ambient;
}
