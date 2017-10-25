#pragma once
#include "ControlObject.h"
class ObjectWithTarget : public ControlObject
{
protected:
    glm::vec3 target;
public:
    ObjectWithTarget(int, glm::vec3 worldPosition, glm::vec3 targetPosition);
    ~ObjectWithTarget();

    void setTarget(glm::vec3);
    glm::vec3 getTarget() const;

};

