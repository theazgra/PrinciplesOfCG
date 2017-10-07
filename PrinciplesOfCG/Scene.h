#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

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
    
    Shader* basicSceneShader;
    
    char* sceneName;
public:
    Scene(char*, Shader*);
    ~Scene();

    
    char* getSceneName() const;
    void addDrawableObject(std::vector<float>);
    void addDrawableObject(std::vector<float>, Shader* shader);

    std::vector<DrawableObject*> const& getDrawableObjects() const;
    Shader const& getBasicShader() const;

    
    


};


