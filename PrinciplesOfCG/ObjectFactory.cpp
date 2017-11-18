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
    std::vector<AssimpVertex> objectData = AssimpLoader::getVertexObjects(file).at(0);
    
    DrawableObject * drawableObject = new DrawableObject(id, objectData, shaderId, textureId);

    return drawableObject;
}

DrawableObject ObjectFactory::createAssimpObject(std::vector<AssimpVertex> vertices, int id, int shaderId, int textureId)
{
    DrawableObject drawableObject(id, vertices, shaderId, textureId);

    return drawableObject;
}

DrawableObject ObjectFactory::createRawObject(std::vector<float> rawData, int id, int shaderId, int textureId)
{
    DrawableObject drawableObject(id, rawData, shaderId, textureId);

    return drawableObject;
}
