#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight()
{
}

PointLight::PointLight(int objectId, glm::vec3 intensity) : Light(objectId, intensity)
{
    this->constant = 0.6f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;
}

PointLight::~PointLight()
{
}

void PointLight::setConstantFallof(float value)
{                
    this->constant = value;
}

void PointLight::setLinearFallof(float value)
{                
    this->linear = value;
}

void PointLight::setQuadraticFallof(float value)
{
    this->quadratic = value;
}

float PointLight::getConstantFallof() const
{
    return this->constant;
}

float PointLight::getLinearFallof() const
{
    return this->linear;
}

float PointLight::getQuadraticFallof() const
{
    return this->quadratic;
}

LightStruct PointLight::getLightInfo()
{
    LightStruct lightInfo;
    lightInfo.lightType = POINT_LIGHT;

    lightInfo.position = this->worldPosition;
    lightInfo.ambientStrength = this->ambientStrength;
    lightInfo.lightColor = this->lightColor;
    lightInfo.specularStrength = this->specularStrength;
    lightInfo.constantFallOff = this->constant;
    lightInfo.linearFallOff = this->linear;
    lightInfo.quadraticFallOff = this->quadratic;
    lightInfo.power = this->power;

    return lightInfo;
}