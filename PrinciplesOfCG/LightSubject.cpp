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

void LightSubject::notifyObservers(unsigned int lightId, LightStruct lightInfo)
{
    for (LightObserver & observer : this->lightObservers)
    {
        observer.lightNotify(lightId, lightInfo);
    }
}

//glm::vec3 LightSubject::getAmbient()
//{
//    return glm::vec3(0);
//}
