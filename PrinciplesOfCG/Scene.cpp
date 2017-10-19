#include "stdafx.h"
#include "Scene.h"


Scene::Scene(char* sceneName, Shader* shader, Camera* camera)
{
    this->sceneName = sceneName;

    int index = shaders.size();
    shaders[index] = shader;
    BASIC_SHADER_ID = index;

    cameras.push_back(camera);
    internalSetActiveCamera(camera);


    //basic point light
    pointLight = PointLight(
        0,
        glm::vec3(0.2f, 13.0f, -0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        50);
    pointLight.registerObserver(*this);
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

DrawableObject& Scene::addDrawableObject(std::vector<float> vec)
{
    DrawableObject* drawable = new DrawableObject(drawableObjects.size(), vec, BASIC_SHADER_ID);
    drawableObjects.push_back(drawable);
    return *drawable;
}

DrawableObject& Scene::addDrawableObject(std::vector<float> vec, Shader * shader)
{
    int index = shaders.size();
    shaders[index] = shader;
    DrawableObject* drawable = new DrawableObject(drawableObjects.size(), vec, index);
    drawableObjects.push_back(drawable);
    return *drawable;
}

DrawableObject& Scene::addDrawableObject(std::vector<float> vec, unsigned int shaderId)
{
    DrawableObject* drawable = new DrawableObject(drawableObjects.size(), vec, shaderId);
    drawableObjects.push_back(drawable);
    return *drawable;
}

SphereObject& Scene::addSphere()
{
    SphereObject * sphere = new SphereObject(drawableObjects.size(), BASIC_SHADER_ID);
    drawableObjects.push_back(sphere);
    this->pointLight.forceUpdate();
    return *sphere;
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

void Scene::swapCamera()
{
    unsigned int camCount = cameras.size();
    unsigned int activeCamId = activeCamera->getObjectId();
    setActiveCamera((activeCamId + 1) % camCount);
}

void Scene::cameraNotify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    for (int i = 0; i < shaders.size(); i++)
    {
        shaders.at(i)->setCameraMatrices(viewMatrix, projectionMatrix);
    }
}

void Scene::lightNotify(glm::vec3 worldPosition, glm::vec3 lightIntensity, glm::vec3 ambient, float power)
{
    for (int i = 0; i < shaders.size(); i++)
    {
        shaders.at(i)->setLightParameters(worldPosition, lightIntensity, ambient, power);
    }
}


PointLight & Scene::getPointLight()
{
    return pointLight;
}



