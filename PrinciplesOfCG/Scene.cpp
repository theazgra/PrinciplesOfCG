#include "stdafx.h"
#include "Scene.h"


Scene::Scene(char* sceneName, Shader* shader, Camera* camera)
{
    this->sceneName = sceneName;
   
    int index = shaders.size();
    shaders[index] = shader;
    
    cameras.push_back(camera);
    internalSetActiveCamera(camera);
}

void Scene::internalSetActiveCamera(Camera * camera)
{
    if (activeCamera != NULL)
    {
        activeCamera->clearObservers();
    }

    activeCamera = camera;
    
    registerCameraObservers();
}

void Scene::registerCameraObservers()
{
    if (activeCamera != NULL)
    {
        activeCamera->clearObservers();
    }

    for (unsigned int i = 0; i < shaders.size(); i++)
    {
        activeCamera->registerObserver(*shaders.at(i));
        shaders.at(i)->setCamera(activeCamera);
    }
}

Scene::~Scene()
{
    for (unsigned int i = 0; i < drawableObjects.size(); i++)
    {
        delete drawableObjects.at(i);
    }
    drawableObjects.clear();

    for (unsigned int i = 0; i < cameras.size(); i++)
    {
        delete cameras.at(i);
    }
    cameras.clear();

    for (unsigned int i = 0; i < lights.size(); i++)
    {
        delete lights.at(i);
    }
    lights.clear();


    for (unsigned int i = 0; i < shaders.size(); i++)
    {
        delete shaders.at(i);
    }
    shaders.empty();

}

char * Scene::getSceneName() const
{
    return sceneName;
}

void Scene::addDrawableObject(std::vector<float> vec)
{
    drawableObjects.push_back(new DrawableObject(drawableObjects.size(), vec, BASIC_SHADER_ID));
}

void Scene::addDrawableObject(std::vector<float> vec, Shader * shader)
{
    int index = shaders.size();
    shaders[index] = shader;
    drawableObjects.push_back(new DrawableObject(drawableObjects.size(), vec, index));
    registerCameraObservers();
}

void Scene::addDrawableObject(std::vector<float> vec, unsigned int shaderId)
{
    drawableObjects.push_back(new DrawableObject(drawableObjects.size(), vec, shaderId));
}

void Scene::addCamera(glm::vec3 worldPos, glm::vec3 targetPos)
{
    Camera* newCam = new Camera(cameras.size(), worldPos, targetPos);
    cameras.push_back(newCam);
    internalSetActiveCamera(newCam);    
}

void Scene::setActiveCamera(unsigned int cameraId)
{
    bool found = false;
    for (unsigned int i = 0; i < cameras.size(); i++)
    {
        if (cameras.at(i)->getObjectId() == cameraId)
        {
            found = true;
            internalSetActiveCamera(cameras.at(i));
            break;
        }
    }
    if (!found)
    {
        printf("Camera with id: %i was not found.", cameraId);
    }
}

std::vector<Camera*> const & Scene::getCameras() const
{
    return cameras;
}

std::vector<DrawableObject*> const& Scene::getDrawableObjects() const
{
    return drawableObjects;
}

Shader const& Scene::getBasicShader() const
{
    return *(shaders.at(BASIC_SHADER_ID));
}

Shader const & Scene::getShader(unsigned int shaderId) const
{
    if (shaders.count(shaderId))
    {
        return *(shaders.at(shaderId));
    }
    else 
    {
        printf("Shader with id: %i, was not found! Will return basic shader.", shaderId);
        return *(shaders.at(BASIC_SHADER_ID));
    }
}

Camera const & Scene::getActiveCamera() const
{
    return *activeCamera;
}

Camera & Scene::getActiveCameraRef()
{
    return *activeCamera;
}



