#include "stdafx.h"
#include "Object.h"


void Object::setModelMatrix(glm::mat4 newMatrix)
{
    this->objectMatrix = newMatrix;
}

Object::Object(int objectId)
{
    this->objectId = objectId;
    this->objectMatrix = glm::mat4(1.0f);
}

Object::~Object()
{
    objectId = -1;
}

void Object::rotate(float angle, glm::vec3 axis)
{
    glm::mat4 rotateMatrix = glm::rotate(angle, axis);
    objectMatrix = objectMatrix * rotateMatrix;
}

void Object::translate(glm::vec3 translateVector)
{
    glm::mat4 translateMatrix = glm::translate(glm::mat4(), translateVector);
    objectMatrix = objectMatrix * translateMatrix;
}

int Object::getObjectId() const
{
    return objectId;
}

glm::mat4 Object::getObjectMatrix() const
{
    return objectMatrix;
}


