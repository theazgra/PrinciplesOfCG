#include "stdafx.h"
#include "CameraSubject.h"


CameraSubject::CameraSubject()
{
}


CameraSubject::~CameraSubject()
{
}

void CameraSubject::notifyObservers(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    for (CameraObserver & observer : cameraObservers)
    {
        observer.notify(viewMatrix, projectionMatrix);
    }
}

void CameraSubject::registerObserver(CameraObserver & cameraObserver)
{
    cameraObservers.push_back(cameraObserver);
}

void CameraSubject::clearObservers()
{
    cameraObservers.clear();
}
