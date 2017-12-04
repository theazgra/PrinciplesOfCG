#pragma once
#include "DrawableObject.h"

#include "models\sphere.h"



class SphereObject : public DrawableObject
{
public:
    SphereObject(int id, int shaderId, int textureId);
    ~SphereObject();
};

