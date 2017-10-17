#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <map>

#include "SphereObject.h"
#include "Camera.h"
#include "Light.h"
#include "Shader.h"

class Scene
{
private:
    int BASIC_SHADER_ID = 0;

    std::vector<DrawableObject*> drawableObjects;
    std::vector<Camera*> cameras;
    std::vector<Light*> lights;
    std::map<int, Shader*> shaders;
 
    char* sceneName;

    Camera* activeCamera = NULL;

    void internalSetActiveCamera(Camera*);
    void registerCameraObservers();
public:
    Scene(char*, Shader*, Camera*);
    ~Scene();
    char* getSceneName() const;

    
    DrawableObject& addDrawableObject(std::vector<float>);
    DrawableObject& addDrawableObject(std::vector<float>, Shader* shader);
    DrawableObject& addDrawableObject(std::vector<float>, unsigned int);
    SphereObject& addSphere();
    std::vector<DrawableObject*> const& getDrawableObjects() const;

    Shader const& getBasicShader() const;
    Shader const& getShader(unsigned int) const;

    Camera& addCamera(glm::vec3, glm::vec3);
    void setActiveCamera(unsigned int cameraId);
    std::vector<Camera*> const& getCameras() const;
    Camera const& getActiveCamera() const;
    Camera& getActiveCameraRef();

};


