#pragma once
#include <glm\glm.hpp>
const unsigned int POINT_LIGHT = 1;
const unsigned int DIRECTIONAL_LIGHT = 2;
const unsigned int SPOT_LIGHT = 3;

struct LightStruct
{
    unsigned int lightType;

    glm::vec3 position;
    glm::vec3 direction;

    float cutOff;
    float outerCutOff;

    glm::vec3 lightColor;
    float ambientStrength;
    float specularStrength;

    float constantFallOff;
    float linearFallOff;
    float quadraticFallOff;

    float power;
};
