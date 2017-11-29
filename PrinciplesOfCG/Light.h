#pragma once
#include "ControlObject.h"
#include "LightSubject.h"

class Light : public ControlObject, public LightSubject
{

protected:
    Light();
    int lightType;

    glm::vec3 lightColor;
    float ambientStrength;
    float specularStrength;
    float power;
public:
    Light(int objectId, glm::vec3 intensity);
    ~Light();
    
    virtual LightStruct getLightInfo();

    void setLightColor(glm::vec3);
    void setPower(float);
    void setAmbientStrength(float ambient);
    void setSpeculatStrength(float specular);

    float getPower() const;
    glm::vec3 getLightColor() const;
    float getAmbientStrength() const;
    float getSpecularStrength() const;

    void move(glm::vec3 vector) override;
    void setPosition(glm::vec3 position) override;

    void forceUpdate();
};

