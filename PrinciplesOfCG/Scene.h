#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

#include "DrawableObject.h"
#include "Shader.h"



class Scene
{
private:
    std::vector<DrawableObject*>* drawableObjects;
    std::vector<DrawableObject*>* cameras;
    std::vector<DrawableObject*>* lights;

    Shader* basicSceneShader;
public:
    Scene(char*, Shader*);
    ~Scene();

    char* sceneName;
    void addObject(std::vector<float>);
    void addObject(std::vector<float>, Shader shader);

    std::vector<DrawableObject*> const& getDrawableObjects() const;
    Shader const& getBasicShader() const;

    
    


};


