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
 
    char* sceneName;

    Camera* activeCamera = NULL;

    void internalSetActiveCamera(Camera*);
    DrawableObject * skyBox = NULL;
    glm::vec3 oldSkyBoxPosition = glm::vec3(0.0f);
public:
    Scene(char*, Camera*);
    ~Scene();
    char* getSceneName() const;

    void addDrawableObject(DrawableObject * drawableObject);
    void addLight(Light * light);
    void addSkyBox(DrawableObject * drawableObject);

    DrawableObject * getSkybox() const;
    
    SphereObject& addSphere(unsigned int shaderId);
    PlainObject& addPlainObject();

    std::vector<DrawableObject*> const& getDrawableObjects() const;
    std::vector<Light*> & getLights();

    Camera& addCamera(glm::vec3, glm::vec3);
    void setActiveCamera(unsigned int cameraId);
    std::vector<Camera*> const& getCameras() const;
    Camera const& getActiveCamera() const;
    Camera& getActiveCameraRef();

    void swapCamera();


    void cameraNotify(glm::mat4, glm::mat4, glm::vec3) override;
    void lightNotify(unsigned int lightId, LightStruct lightInfo) override;

};


