#include "stdafx.h"
#include "Light.h"


Light::Light()
{
}

Light::Light(int objectId, glm::vec3 worldPosition, glm::vec3 intensity, float power) : ControlObject(objectId, worldPosition)
{
    this->intensity = intensity;
    this->power = power;
}

Light::~Light()
{
}

void Light::setIntensity(glm::vec3 intensity)
{
    this->intensity = intensity;
}

void Light::setPower(float power)
{
    this->power = power;
    notifyObservers(this->worldPosition, this->intensity, glm::vec3(0), this->power);
}

void Light::forceUpdate()
{
    notifyObservers(this->worldPosition, this->intensity, glm::vec3(0), this->power);
}

float Light::getPower() const 
{
    return this->power;
}

glm::vec3 Light::getIntensity() const
{
    return this->intensity;
}

