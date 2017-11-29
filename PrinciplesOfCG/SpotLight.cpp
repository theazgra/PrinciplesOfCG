#include "stdafx.h"
#include "SpotLight.h"


//radians, 12.5, 17.5
SpotLight::SpotLight(int objectId, glm::vec3 intensity, float cutOff, float outerCutOff, glm::vec3 direction)
    : Light(objectId, intensity)
{
    this->direction = direction;

    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;

    this->constant = 1.0f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;
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

    lightInfo.position = this->worldPosition;
    lightInfo.direction = this->direction;

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