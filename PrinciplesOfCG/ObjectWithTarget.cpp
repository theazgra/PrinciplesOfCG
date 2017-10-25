#include "stdafx.h"
#include "ObjectWithTarget.h"


ObjectWithTarget::ObjectWithTarget(int objectId, glm::vec3 worldPosition, glm::vec3 target) : ControlObject(objectId, worldPosition)
{
    this->target = glm::vec3(
        target.x - worldPosition.x,
        target.y - worldPosition.y,
        target.z - worldPosition.z
    );
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
