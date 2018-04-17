#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <map>
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
 
    const char* sceneName;
    bool playerCamIsActive = false;

    Camera* activeCamera = NULL;

    void internalSetActiveCamera(Camera*);
    DrawableObject * skyBox = NULL;
    Light * shadowLight = NULL;
    glm::vec3 oldSkyBoxPosition = glm::vec3(0.0f);
public:
    Scene(const char *, Camera * = nullptr);
    ~Scene();
    const char* getSceneName() const;

    void addDrawableObject(DrawableObject * drawableObject);
    void addLight(Light * light);
    void addSkyBox(DrawableObject * drawableObject);
    void addShadowLight(Light * light);

    DrawableObject * getSkybox() const;

    std::vector<DrawableObject*> const& getDrawableObjects() const;
    std::vector<Light*> & getLights();

    Camera& addCamera(glm::vec3 worldPos, glm::vec3 targetPos, bool playerCam = false);
    void setActiveCamera(unsigned int cameraId);
    std::vector<Camera*> const& getCameras() const;
    Camera const& getActiveCamera() const;
    Camera& getActiveCameraRef();

    void swapCamera();


    void cameraNotify(glm::mat4, glm::mat4, glm::vec3) override;
    void lightNotify(unsigned int lightId, LightStruct lightInfo) override;
    Light* getShadowLight();

    void deleteObject(int id);
    bool renderCrosshair() const;
    DrawableObject* getCrosshair();
};


