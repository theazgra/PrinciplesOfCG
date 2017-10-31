#include "stdafx.h"
#include "LightSubject.h"


LightSubject::LightSubject()
{
}


LightSubject::~LightSubject()
{
}

void LightSubject::registerObserver(LightObserver & observer)
{
    this->lightObservers.push_back(observer);
}

void LightSubject::clearObservers()
{
    this->lightObservers.clear();
}

void LightSubject::notifyObservers(glm::vec3 worldPosition, glm::vec3 lightIntensity, glm::vec3 ambient, float power)
{
    for (LightObserver & observer : this->lightObservers)
    {
        observer.lightNotify(worldPosition, lightIntensity, ambient, power);
    }
}

//glm::vec3 LightSubject::getAmbient()
//{
//    return glm::vec3(0);
//}
