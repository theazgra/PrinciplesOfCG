#include "stdafx.h"
#include "DirectionalLight.h"




DirectionalLight::DirectionalLight(int objectId, glm::vec3 intensity, glm::vec3 direction) : Light(objectId, intensity)
{
    this->lightDirection = direction;
}

DirectionalLight::~DirectionalLight()
{
}

LightStruct DirectionalLight::getLightInfo()
{
    LightStruct lightInfo;
    lightInfo.lightType = DIRECTIONAL_LIGHT;
    lightInfo.direction = this->lightDirection;
    lightInfo.ambientStrength = this->ambientStrength;
    lightInfo.lightColor = this->lightColor;
    lightInfo.specularStrength = this->specularStrength;
    lightInfo.power = this->power;

    return lightInfo;

}
