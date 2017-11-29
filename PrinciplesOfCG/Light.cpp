#include "stdafx.h"
#include "Light.h"


Light::Light()
{
}

Light::Light(int objectId, glm::vec3 intensity) : 
    ControlObject(objectId, glm::vec3(0.0f, 0.0f, 0.0f))
{
    this->ambientStrength = 0.2f;
    this->specularStrength = 0.5f;
    this->lightColor = intensity;
    this->power = 1.0f;
    
    notifyObservers(getObjectId(), getLightInfo());
}

Light::~Light()
{
}

LightStruct Light::getLightInfo()
{
    return LightStruct();
}

void Light::setLightColor(glm::vec3 intensity)
{
    this->lightColor = intensity;
    notifyObservers(getObjectId(), getLightInfo());
}

void Light::setPower(float power)
{
    this->power = power;
    notifyObservers(getObjectId(), getLightInfo());
}

void Light::forceUpdate()
{
    notifyObservers(getObjectId(), getLightInfo());
}

float Light::getPower() const 
{
    return this->power;
}

glm::vec3 Light::getLightColor() const
{
    return this->lightColor;
}

void Light::move(glm::vec3 vector)
{
    ControlObject::move(vector);
    notifyObservers(getObjectId(), getLightInfo());
}

void Light::setPosition(glm::vec3 position)
{
    ControlObject::setPosition(position);
    notifyObservers(getObjectId(), getLightInfo());
}

float Light::getAmbientStrength() const
{
    return this->ambientStrength;
}

float Light::getSpecularStrength() const
{
    return this->specularStrength;
}

void Light::setAmbientStrength(float ambient)
{
    this->ambientStrength = ambient;
    notifyObservers(getObjectId(), getLightInfo());
}

void Light::setSpeculatStrength(float specular)
{
    this->specularStrength = specular;
}

