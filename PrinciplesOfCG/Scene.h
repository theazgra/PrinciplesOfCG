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
    const unsigned int BASIC_SHADER_ID = 0;

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

    
    void addDrawableObject(std::vector<float>);
    void addDrawableObject(std::vector<float>, Shader* shader);
    void addDrawableObject(std::vector<float>, unsigned int);
    void addSphere();
    std::vector<DrawableObject*> const& getDrawableObjects() const;

    Shader const& getBasicShader() const;
    Shader const& getShader(unsigned int) const;

    void addCamera(glm::vec3, glm::vec3);
    void setActiveCamera(unsigned int cameraId);
    std::vector<Camera*> const& getCameras() const;
    Camera const& getActiveCamera() const;
    Camera & getActiveCameraRef();

};


