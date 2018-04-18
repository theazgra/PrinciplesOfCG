#include "stdafx.h"
#include "Random.h"


Random::Random()
{
}


Random::~Random()
{
}

int Random::rand(int max)
{
    return rand(0, max);
}

int Random::rand(int min, int max)
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

    int val = uni(rng);
    return val;
}

glm::vec3 Random::randVec3()
{
    int x = rand();
    int y = rand();
    int z = rand();

    return glm::vec3(x, y, z);
}

glm::vec3 Random::normRandVec3()
{
    return glm::normalize(randVec3());
}

glm::vec3 Random::randForCurve(int min, int max)
{
    return glm::vec3(rand(min, max), 0, rand(min, max));
}
