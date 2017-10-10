#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <map>

#include "DrawableObject.h"
#include "Camera.h"
#include "Light.h"
#include "Shader.h"



class Scene
{
private:
    std::vector<DrawableObject*>* drawableObjects;
    std::vector<Camera*>* cameras;
    std::vector<Light*>* lights;

    std::map<int, Shader*> shaders;
    
    Shader* basicSceneShader;
    
    char* sceneName;

    Camera* activeCamera;
public:
    Scene(char*, Shader*, Camera*);
    ~Scene();

    
    char* getSceneName() const;
    void addDrawableObject(std::vector<float>);
    void addDrawableObject(std::vector<float>, Shader* shader);

    void addCamera(Camera*);

    std::vector<DrawableObject*> const& getDrawableObjects() const;
    Shader const& getBasicShader() const;

    Camera const& getActiveCamera() const;
};


