#pragma once
#include <random>
#include "glm/glm.hpp"

class Random
{
public:
    Random();
    ~Random();
    int rand(int max = 100);
    int rand(int min, int max);
    glm::vec3 randVec3();
    glm::vec3 normRandVec3();

    glm::vec3 randForCurve(int min = -50, int max = 50);

};


