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

    std::vector<DrawableObject*> drawableObjects;
    std::vector<Camera*> cameras;
    std::vector<Light*> lights;
    std::vector<unsigned int> sceneShaderIds;
    PointLight pointLight;
 
    char* sceneName;

    Camera* activeCamera = NULL;

    void internalSetActiveCamera(Camera*);
public:
    Scene(char*, Camera*);
    ~Scene();
    char* getSceneName() const;

    void addDrawableObject(DrawableObject * drawableObject);
    
    SphereObject& addSphere(unsigned int shaderId);
    PlainObject& addPlainObject();

    std::vector<DrawableObject*> const& getDrawableObjects() const;

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


