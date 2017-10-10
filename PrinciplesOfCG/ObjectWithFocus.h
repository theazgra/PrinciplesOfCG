#pragma once
#include "Object.h"
class ObjectWithFocus : public Object
{
protected:
    glm::vec3 target;
    glm::vec3 worldPosition;
public:
    ObjectWithFocus(int, glm::vec3, glm::vec3);
    ~ObjectWithFocus();

    void lookAt(glm::vec3);
    void lookAtObject(Object const&);
};

