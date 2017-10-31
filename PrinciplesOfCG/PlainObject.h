#pragma once
#include "DrawableObject.h"
#include "models\plain.h"

class PlainObject : public DrawableObject
{
public:
    PlainObject(int, int);
    ~PlainObject();
};

