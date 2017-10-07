#include "stdafx.h"
#include "Scene.h"

Scene::Scene(char* sceneName, Shader* shader)
{
    this->sceneName = sceneName;
    this->basicSceneShader = shader;
    
    drawableObjects = new std::vector<DrawableObject*>();
}

Scene::~Scene()
{
    for (int i = 0; i < drawableObjects->size(); i++)
    {
        delete drawableObjects->at(i);
    }

    drawableObjects->clear();
    delete drawableObjects;
    delete basicSceneShader;
}

void Scene::addObject(std::vector<float> vec)
{
    drawableObjects->push_back(new DrawableObject(drawableObjects->size(), vec));
}

void Scene::addObject(std::vector<float> vec, Shader shader)
{
    drawableObjects->push_back(new DrawableObject(drawableObjects->size(), vec, shader));
}

std::vector<DrawableObject*> const& Scene::getDrawableObjects() const
{
    return *drawableObjects;
}

Shader const& Scene::getBasicShader() const
{
    return *basicSceneShader;
}


