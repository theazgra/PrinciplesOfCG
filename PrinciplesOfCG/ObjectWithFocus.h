#pragma once
#include "Object.h"
class ObjectWithFocus : public Object
{
protected:
    glm::mat4 PoI;
public:
    ObjectWithFocus(int, glm::mat4);
    ~ObjectWithFocus();

    void lookAt(glm::mat4);
    void lookAtObject(Object const&);
};

