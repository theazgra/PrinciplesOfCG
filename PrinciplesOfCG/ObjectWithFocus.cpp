#include "stdafx.h"
#include "ObjectWithFocus.h"


ObjectWithFocus::ObjectWithFocus(int objectId, glm::vec3 worldPosition, glm::vec3 PoI) : Object(objectId)
{
    this->target = PoI;
    this->worldPosition = worldPosition;
}


ObjectWithFocus::~ObjectWithFocus()
{
}

void ObjectWithFocus::lookAt(glm::vec3 position)
{
    this->target = position;
}

void ObjectWithFocus::lookAtObject(Object const& object)
{
    //this->PoI = object.getObjectMatrix();
}
