#include "stdafx.h"
#include "ObjectWithFocus.h"


ObjectWithFocus::ObjectWithFocus(int objectId, glm::mat4 PoI) : Object(objectId)
{
    this->PoI = PoI;
}


ObjectWithFocus::~ObjectWithFocus()
{
}

void ObjectWithFocus::lookAt(glm::mat4 position)
{
    this->PoI = position;
}

void ObjectWithFocus::lookAtObject(Object const& object)
{
    this->PoI = object.getObjectMatrix();
}
