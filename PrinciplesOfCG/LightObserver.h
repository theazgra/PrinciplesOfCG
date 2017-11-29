#pragma once
#include "LightStruct.h"
class LightObserver
{
public:
    virtual void lightNotify(unsigned int lightId, LightStruct lightInfo) = 0;
};

