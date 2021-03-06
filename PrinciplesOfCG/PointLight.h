#pragma once
#include "Light.h"
class PointLight : public Light
{
private:
    
    float constant;
    float linear;
    float quadratic;
public:
    PointLight();
    PointLight(int objectId, glm::vec3 lightIntensity);
    ~PointLight();

    void setConstantFallof(float value);
    void setLinearFallof(float value);
    void setQuadraticFallof(float value);

    float getConstantFallof() const;
    float getLinearFallof() const;
    float getQuadraticFallof() const;

    LightStruct getLightInfo() override;
};

