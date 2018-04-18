#include "stdafx.h"
#include "Scene.h"

#include "Application.h"


void Scene::spawnDebris(glm::vec3 origin, int count)
{
    Random random;
    DrawableObject * debri = ObjectFactory::createAssimpObject("objekty/debris.obj", Application::getInstance()->getNextId(), 0, 9);
    glm::mat4 identity = glm::mat4(1.0f);
    identity = glm::translate(identity, origin);
    identity =  glm::scale(identity, glm::vec3(5.0f));
    debri->setObjectMatrix(identity);


    for (size_t i = 0; i < count; i++)
    {
        DrawableObject* d2 = new DrawableObject(*debri);
        d2->changeId(Application::getInstance()->getNextId());

        d2->moveInDirection(random.normRandVec3() * 0.1f, random.rand(500));
        this->drawableObjects.push_back(d2);
    }
}

Scene::Scene(const char* sceneName, Camera * camera)
{
    this->sceneName = sceneName;

    if (camera != nullptr)
    {
        cameras.push_back(camera);
        internalSetActiveCamera(camera);
    }
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

const char * Scene::getSceneName() const
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

Camera& Scene::addCamera(glm::vec3 worldPos, glm::vec3 targetPos, bool playerCam)
{
    Camera* newCam = new Camera(cameras.size(), worldPos, targetPos, playerCam);
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
            if (cameras.at(i)->isPlayerCam())
                this->playerCamIsActive = true;
            else
                this->playerCamIsActive = false;

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

Light * Scene::getShadowLight()
{
    return this->shadowLight;
}

void Scene::destroyObject(int id)
{
    for (int i = 0; i < this->drawableObjects.size(); i++)
    {
        if (drawableObjects.at(i)->getObjectId() == id)
        {
            if (drawableObjects.at(i)->isDestructable())
            {
                glm::vec3 objPosition = drawableObjects.at(i)->getPosition();
                spawnDebris(objPosition, 10);
                delete drawableObjects.at(i);
                drawableObjects.erase(drawableObjects.begin() + i);

                break;
            }
        }
    }
}

bool Scene::renderCrosshair() const
{
    return this->playerCamIsActive;
}

DrawableObject * Scene::getCrosshair()
{
    for (size_t i = 0; i < this->drawableObjects.size(); i++)
    {
        if (this->drawableObjects.at(i)->isCrosshair())
            return this->drawableObjects.at(i);
    }

    return nullptr;
}

void Scene::checkObjectToDelete()
{
    for (size_t i = 0; i < this->drawableObjects.size(); i++)
    {
        if (this->drawableObjects.at(i)->shouldBeDeleted())
        {
            delete drawableObjects.at(i);
            drawableObjects.erase(drawableObjects.begin() + i);
            break;
        }
    }
}

void Scene::shootBullet()
{
    DrawableObject * bullet = ObjectFactory::createAssimpObject("objekty/bullet.obj", Application::getInstance()->getNextId(), 0, 9);
    glm::vec3 playerPosition = this->activeCamera->getWorldPosition();
    glm::vec3 direction = glm::normalize(this->activeCamera->getTarget()) ; //* 2.0f
    bullet->translate(playerPosition);
    bullet->moveInDirection(direction, 200);
    this->drawableObjects.push_back(bullet);
}

void Scene::spawnZombies(int count)
{
    Random random;
    DrawableObject * zombie = ObjectFactory::createAssimpObject("objekty/zombie.obj", Application::getInstance()->getNextId(), 0, 6);
    zombie->setDestructable(true);

    for (size_t i = 0; i < count; i++)
    {
        DrawableObject* zombieCopy = new DrawableObject(*zombie);
        zombieCopy->setDestructable(true);
        zombieCopy->changeId(Application::getInstance()->getNextId());

        float t_increment = 0.005f;
        zombieCopy->initializeBezierCurve(
            random.randForCurve(),
            random.randForCurve(),
            random.randForCurve(),
            random.randForCurve(),
            t_increment);
        

        this->drawableObjects.push_back(zombieCopy);
    }


   


    
}





