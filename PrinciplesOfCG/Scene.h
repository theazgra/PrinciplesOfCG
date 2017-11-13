#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <map>

#include "SphereObject.h"
#include "PlainObject.h"
#include "CameraObserver.h"
#include "Camera.h"
#include "PointLight.h"
#include "Shader.h"

class Scene : public CameraObserver, public LightObserver
{
private:
    int BASIC_SHADER_ID = 0;

    std::vector<DrawableObject*> drawableObjects;
    std::vector<Camera*> cameras;
    std::vector<Light*> lights;
    std::map<int, Shader*> shaders;
    PointLight pointLight;
 
    char* sceneName;

    Camera* activeCamera = NULL;

    void internalSetActiveCamera(Camera*);
public:
    Scene(char*, Shader*, Camera*);
    ~Scene();
    char* getSceneName() const;

    
    DrawableObject& addDrawableObject(std::vector<float>);
    DrawableObject& addDrawableObject(std::vector<float>, Shader* shader);
    DrawableObject& addDrawableObject(std::vector<float>, unsigned int);
    
    SphereObject& addSphere();
    SphereObject& addSphere(Shader* shader);
    PlainObject& addPlainObject();

    std::vector<DrawableObject*> const& getDrawableObjects() const;

    Shader const& getBasicShader() const;
    Shader const& getShader(unsigned int) const;

    Camera& addCamera(glm::vec3, glm::vec3);
    void setActiveCamera(unsigned int cameraId);
    std::vector<Camera*> const& getCameras() const;
    Camera const& getActiveCamera() const;
    Camera& getActiveCameraRef();

    void swapCamera();


    void cameraNotify(glm::mat4, glm::mat4, glm::vec3) override;
    void lightNotify(glm::vec3, glm::vec3, glm::vec3, float) override;

    PointLight& getPointLight();

};


