#include "stdafx.h"
#include "ControlObject.h"


ControlObject::ControlObject()
{
}

ControlObject::ControlObject(int objectId, glm::vec3 worldPosition) : Object(objectId)
{
    this->worldPosition = worldPosition;
}

ControlObject::~ControlObject()
{
}

void ControlObject::move(glm::vec3 vector)
{
    this->worldPosition += vector;
}

void ControlObject::setPosition(glm::vec3 position)
{
    this->worldPosition = position;
}

glm::vec3 ControlObject::getWorldPosition() const
{
    return this->worldPosition;
}
