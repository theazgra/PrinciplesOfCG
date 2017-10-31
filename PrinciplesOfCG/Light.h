#pragma once
#include "ControlObject.h"
#include "LightSubject.h"
class Light : public ControlObject, public LightSubject
{

protected:
    Light();

    glm::vec3 intensity;
    virtual glm::vec3 getAmbient() = 0;
    float power;
public:
    
    Light(int, glm::vec3, glm::vec3, float);
    ~Light();
    void setIntensity(glm::vec3);
    void setPower(float);

    float getPower() const;
    glm::vec3 getIntensity() const;

    void forceUpdate();
    
};

