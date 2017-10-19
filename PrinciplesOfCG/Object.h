#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Object
{
private:
    int objectId;

protected:
    Object();

public:
    Object(int objectId);
    ~Object();

    int getObjectId() const;
};

