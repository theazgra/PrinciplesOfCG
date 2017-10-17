#pragma once
#include "CameraObserver.h"
#include <vector>
class CameraSubject
{
private:
    std::vector<std::reference_wrapper<CameraObserver>> cameraObservers;
public:
    CameraSubject();
    ~CameraSubject();
    virtual void registerObserver(CameraObserver&);
    void clearObservers();
protected:
    void notifyObservers(glm::mat4, glm::mat4);
};

