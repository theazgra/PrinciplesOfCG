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

    return drawableObject;
}


DrawableObject ObjectFactory::createRawObject(std::vector<float> rawData, int id, int shaderId, int textureId)
{
    DrawableObject drawableObject(id, rawData, shaderId, textureId);

    return drawableObject;
}
