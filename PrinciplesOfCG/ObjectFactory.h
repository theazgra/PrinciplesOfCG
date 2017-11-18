#pragma once
#include "AssimpLoader.h"
#include "DrawableObject.h"
#include "Scene.h"

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
    static DrawableObject createAssimpObject(std::vector<AssimpVertex> vertices, int id, int shaderId = -1, int textureId = -1);
    static DrawableObject createRawObject(std::vector<float> rawData, int id, int shaderId = -1, int textureId = -1);
    static Scene createScene(const char * file, Camera* camera = NULL, PointLight* pointLight = NULL);

    //scena bude mit addShader(Shader), getShader(int)
    //addDrawableObject(DrawableObject) drawbale object dostaneme pouze z ObjectFactory
    //ObjectFactory bude umet vytvorit i scenu pomoci assimpu
};

