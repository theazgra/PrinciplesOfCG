#include "stdafx.h"
#include "SpotLight.h"


//radians, 12.5, 17.5
SpotLight::SpotLight(int objectId, glm::vec3 intensity, float cutOff, float outerCutOff, glm::vec3 target)
    : Light(objectId, intensity)
{
    this->direction = target - this->Light::worldPosition;

    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;

    this->constant = 0.5f;
    this->linear = 0.06f;
    this->quadratic = 0.022f;
}

SpotLight::~SpotLight()
{
}

void SpotLight::setCutOff(float value)
{
    this->cutOff = value;
}

void SpotLight::setOuterCutOff(float value)
{
    this->outerCutOff= value;
}

void SpotLight::setConstantFallof(float value)
{
    this->constant = value;
}

void SpotLight::setLinearFallof(float value)
{
    this->linear = value;
}

void SpotLight::setQuadraticFallof(float value)
{
    this->quadratic = value;
}

void SpotLight::setTarget(glm::vec3 target)
{
    this->target = target;
}


float SpotLight::getCutOff() const
{
    return this->cutOff;
}

float SpotLight::getOuterCutOff() const
{
    return this->outerCutOff;
}

float SpotLight::getConstantFallof() const
{
    return this->constant;
}

float SpotLight::getLinearFallof() const
{
    return this->linear;
}

float SpotLight::getQuadraticFallof() const
{
    return this->quadratic;
}

LightStruct SpotLight::getLightInfo()
{
    LightStruct lightInfo;
    lightInfo.lightType = SPOT_LIGHT;

    lightInfo.position = this->Light::worldPosition;
    lightInfo.direction = this->direction;
    lightInfo.target = this->target;

    lightInfo.cutOff = this->cutOff;
    lightInfo.outerCutOff = this->outerCutOff;

    lightInfo.ambientStrength = this->ambientStrength;
    lightInfo.lightColor = this->lightColor;
    lightInfo.specularStrength = this->specularStrength;

    lightInfo.constantFallOff = this->constant;
    lightInfo.linearFallOff = this->linear;
    lightInfo.quadraticFallOff = this->quadratic;
    lightInfo.power = this->power;

    return lightInfo;
}