#include "stdafx.h"
#include "ObjectFactory.h"


ObjectFactory::ObjectFactory()
{

}


ObjectFactory::~ObjectFactory()
{

}

DrawableObject * ObjectFactory::createAssimpObject(const char * file, int id, unsigned int shaderId, unsigned int textureId)
{
    std::tuple<std::vector<AssimpVertex>, std::vector<unsigned int>> objectData = AssimpLoader::getVertexObjects(file).at(0);
    
    
    DrawableObject * drawableObject = new DrawableObject(
        id, 
        std::get<std::vector<AssimpVertex>>(objectData),
        std::get<std::vector<unsigned int>>(objectData),
        shaderId, 
        textureId);

    drawableObject->setObjFile(file);

    return drawableObject;
}


DrawableObject ObjectFactory::createRawObject(std::vector<float> rawData, int id, int shaderId, int textureId)
{
    DrawableObject drawableObject(id, rawData, shaderId, textureId);

    return drawableObject;
}

SphereObject * ObjectFactory::createSphere(int id, int shaderId, int textureId)
{
    SphereObject * sphere = new SphereObject(id, shaderId, textureId);
    return sphere;
}

PlainObject * ObjectFactory::createPlain(int id, int shaderId, int textureId)
{
    PlainObject * plain = new PlainObject(id, shaderId, textureId);
    plain->setObjFile("Plain");
    return plain;
}

PointLight * ObjectFactory::createPointLight(unsigned int id, glm::vec3 intensity)
{
    PointLight * light = new PointLight(id, intensity);
    return light;
}

SpotLight * ObjectFactory::createSpotLight(unsigned int id, glm::vec3 intensity, float cutOff, float outerCutOff, glm::vec3 direction)
{
    SpotLight * light = new SpotLight(id, intensity, cutOff, outerCutOff, direction);
    return light;
}

DirectionalLight * ObjectFactory::createDirectionalLight(unsigned int id, glm::vec3 intensity, glm::vec3 direction)
{
    DirectionalLight * light = new DirectionalLight(id, intensity, direction);
    return light;
}
