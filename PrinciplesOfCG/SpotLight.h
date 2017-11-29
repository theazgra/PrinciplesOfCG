#pragma once
#include "Light.h"
class SpotLight :
    public Light
{
private:
    glm::vec3 direction;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
public:
    SpotLight(int objectId, glm::vec3 intensity, float cutOff, float outerCutOff, glm::vec3 direction);
    ~SpotLight();


    void setCutOff(float value);
    void setOuterCutOff(float value);
    void setConstantFallof(float value);
    void setLinearFallof(float value);
    void setQuadraticFallof(float value);

    float getCutOff() const;
    float getOuterCutOff() const;
    float getConstantFallof() const;
    float getLinearFallof() const;
    float getQuadraticFallof() const;

    LightStruct getLightInfo() override;
};

