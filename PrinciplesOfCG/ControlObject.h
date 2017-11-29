#pragma once
#include "Object.h"
class ControlObject : public Object
{
private:

protected:
    ControlObject();
    glm::vec3 worldPosition;

public:
    ControlObject(int objectId, glm::vec3 worldPosition);
    ~ControlObject();

    virtual void move(glm::vec3 vector);
    virtual void setPosition(glm::vec3 position);

    glm::vec3 getWorldPosition() const;
};

