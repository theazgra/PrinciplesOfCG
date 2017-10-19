#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

Object::Object(int objectId)
{
    this->objectId = objectId;
}

Object::~Object()
{
    objectId = -1;
}

int Object::getObjectId() const
{
    return objectId;
}


