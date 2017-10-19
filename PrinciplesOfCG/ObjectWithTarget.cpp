#include "stdafx.h"
#include "ObjectWithTarget.h"


ObjectWithTarget::ObjectWithTarget(int objectId, glm::vec3 worldPosition, glm::vec3 PoI) : ControlObject(objectId, worldPosition)
{
    this->target = PoI;
}

ObjectWithTarget::~ObjectWithTarget()
{
}

void ObjectWithTarget::setTarget(glm::vec3 targetPosition)
{
    this->target = targetPosition;
}

glm::vec3 ObjectWithTarget::getTarget() const
{
    return this->target;
}
