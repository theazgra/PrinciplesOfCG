#pragma once
#include <vector>
#include "LightObserver.h"

class LightSubject
{
    
private:
    std::vector<std::reference_wrapper<LightObserver>> lightObservers;
public:
    LightSubject();
    ~LightSubject();
    virtual void registerObserver(LightObserver& lightObserver);
    void clearObservers();
protected:
    void notifyObservers(unsigned int lightId, LightStruct lightInfo);
};

