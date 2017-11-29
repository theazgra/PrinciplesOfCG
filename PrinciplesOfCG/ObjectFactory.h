#pragma once
#include "AssimpLoader.h"
#include "DrawableObject.h"
#include "Scene.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

enum ObjectType
{
    RawModel,
    AssimpModel
};

class ObjectFactory
{
public:       
    ObjectFactory();
    ~ObjectFactory();

    static DrawableObject * createAssimpObject(const char * file, int id, unsigned int shaderId = -1, unsigned int textureId = -1);
    static DrawableObject createRawObject(std::vector<float> rawData, int id, int shaderId = -1, int textureId = -1);
    static Scene createScene(const char * file, Camera* camera = NULL, PointLight* pointLight = NULL);

    static PointLight * createPointLight(unsigned int id, glm::vec3 intensity);
    static SpotLight * createSpotLight(unsigned int id, glm::vec3 intensity, float cutOff, float outerCutOff, glm::vec3 direction);
    static DirectionalLight * createDirectionalLight(unsigned int id, glm::vec3 intensity, glm::vec3 direction);
};

