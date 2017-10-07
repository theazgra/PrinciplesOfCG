#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Object
{
private:
    int objectId;
    glm::mat4 objectMatrix;
protected:
    void setModelMatrix(glm::mat4);
public:
    Object(int objectId);
    ~Object();
    
    void rotate(float, glm::vec3);
    void translate(glm::vec3);
    int getObjectId() const;
    glm::mat4 getObjectMatrix() const;

    
};

