#include "stdafx.h"
#include "Scene.h"

Scene::Scene(char* sceneName, Shader* shader, Camera* camera)
{
    this->sceneName = sceneName;
    this->basicSceneShader = shader;
    
    drawableObjects = new std::vector<DrawableObject*>();
    cameras = new std::vector<Camera*>();
    lights = new std::vector<Light*>();

    int i = shaders.size();
    shaders.insert(i, NULL);
    

    cameras->push_back(camera);
    activeCamera = camera;
}

Scene::~Scene()
{
    for (int i = 0; i < drawableObjects->size(); i++)
    {
        delete drawableObjects->at(i);
    }
    drawableObjects->clear();
    delete drawableObjects;

    for (int i = 0; i < cameras->size(); i++)
    {
        delete cameras->at(i);
    }
    cameras->clear();
    delete cameras;

    for (int i = 0; i < lights->size(); i++)
    {
        delete lights->at(i);
    }
    lights->clear();
    delete lights;

    delete basicSceneShader;

}

char * Scene::getSceneName() const
{
    return sceneName;
}

void Scene::addDrawableObject(std::vector<float> vec)
{
    drawableObjects->push_back(new DrawableObject(drawableObjects->size(), vec));
}

void Scene::addDrawableObject(std::vector<float> vec, Shader * shader)
{
    drawableObjects->push_back(new DrawableObject(drawableObjects->size(), vec, shader));
}

void Scene::addCamera(Camera * camera)
{
    cameras->push_back(camera);
    activeCamera = camera;
}

std::vector<DrawableObject*> const& Scene::getDrawableObjects() const
{
    return *drawableObjects;
}

Shader const& Scene::getBasicShader() const
{
    return *basicSceneShader;
}

Camera const & Scene::getActiveCamera() const
{
    return *activeCamera;
}



