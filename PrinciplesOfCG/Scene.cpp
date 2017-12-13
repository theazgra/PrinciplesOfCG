#include "stdafx.h"
#include "Scene.h"

#include "Application.h"


Scene::Scene(char* sceneName, Camera* camera)
{
    this->sceneName = sceneName;

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
    activeCamera->registerObserver(*this);
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

    
}

char * Scene::getSceneName() const
{
    return sceneName;
}

//DrawableObject& Scene::addDrawableObject(std::vector<float> vec)
//{
//    DrawableObject* drawable = new DrawableObject(drawableObjects.size(), vec, BASIC_SHADER_ID);
//    drawableObjects.push_back(drawable);
//    return *drawable;
//}
//
//DrawableObject& Scene::addDrawableObject(std::vector<float> vec, Shader * shader)
//{
//    int index = shaders.size();
//    shaders[index] = shader;
//    DrawableObject* drawable = new DrawableObject(drawableObjects.size(), vec, index);
//    drawableObjects.push_back(drawable);
//    return *drawable;
//}
//
//DrawableObject& Scene::addDrawableObject(std::vector<float> vec, unsigned int shaderId)
//{
//    DrawableObject* drawable = new DrawableObject(drawableObjects.size(), vec, shaderId);
//    drawableObjects.push_back(drawable);
//    return *drawable;
//}

void Scene::addDrawableObject(DrawableObject * drawableObject)
{
    this->drawableObjects.push_back(drawableObject);
    
    bool found = false;
    for (unsigned int i = 0; i < this->sceneShaderIds.size(); i++)
    {
        if (this->sceneShaderIds.at(i) == drawableObject->getShaderId())
        {
            found = true;
        }
    }
    if (!found)
    {
        this->sceneShaderIds.push_back(drawableObject->getShaderId());
    }

    this->activeCamera->forceUpdate();
}

void Scene::addLight(Light * light)
{
    this->lights.push_back(light);
    light->registerObserver(*this);
    light->forceUpdate();
}


void Scene::addShadowLight(Light * light)
{
    this->lights.push_back(light);
    light->registerObserver(*this);
    light->forceUpdate();
    this->shadowLight = light;
}

void Scene::addSkyBox(DrawableObject * drawableObject)
{
    this->drawableObjects.push_back(drawableObject);    
    this->skyBox = drawableObject;
    this->skyBox->setIsSkyBox(true);

    bool found = false;
    for (unsigned int i = 0; i < this->sceneShaderIds.size(); i++)
    {
        if (this->sceneShaderIds.at(i) == drawableObject->getShaderId())
        {
            found = true;
        }
    }
    if (!found)
    {
        this->sceneShaderIds.push_back(drawableObject->getShaderId());
    }

    this->activeCamera->forceUpdate();
}

DrawableObject * Scene::getSkybox() const
{
    return skyBox;
}

Camera& Scene::addCamera(glm::vec3 worldPos, glm::vec3 targetPos)
{
    Camera* newCam = new Camera(cameras.size(), worldPos, targetPos);
    cameras.push_back(newCam);
    internalSetActiveCamera(newCam);    
    return *newCam;
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

std::vector<Light*>& Scene::getLights()
{
    return this->lights;
}

Camera const & Scene::getActiveCamera() const
{
    return *activeCamera;
}

Camera & Scene::getActiveCameraRef()
{
    return *activeCamera;
}

void Scene::swapCamera()
{
    unsigned int camCount = cameras.size();
    unsigned int activeCamId = activeCamera->getObjectId();
    setActiveCamera((activeCamId + 1) % camCount);
    printf("Activated camera with id: %i\n", (activeCamId + 1) % camCount);
}

void Scene::cameraNotify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition)
{
    if (skyBox != NULL) 
    {
        skyBox->translate(cameraPosition - oldSkyBoxPosition);
        oldSkyBoxPosition = cameraPosition;
    }
    

    for (int i = 0; i < this->sceneShaderIds.size(); i++)
    {
        Application::getInstance()->getShader(this->sceneShaderIds.at(i))->setCameraMatrices(
            viewMatrix,
            projectionMatrix,
            cameraPosition);
    }
}

void Scene::lightNotify(unsigned int lightId, LightStruct lightInfo)
{
    for (int i = 0; i < sceneShaderIds.size(); i++)
    {
        Application::getInstance()->getShader(this->sceneShaderIds.at(i))->setLightParameters(
            lightId,
            lightInfo
        );
    }
}

Light & Scene::getShadowLight() const
{
    return *this->shadowLight;
}




