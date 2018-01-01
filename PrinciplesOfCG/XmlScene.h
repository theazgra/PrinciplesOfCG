#pragma once
#include "pugixml.hpp"
#include "Application.h"
#include "ObjectFactory.h"



class XmlScene
{
private:
    //pugi::xml_document document;
    const std::string OBJECT_NODE = "Object";
    const std::string CAMERA_NODE = "Camera";
    const std::string LIGHT_NODE = "Light";
    const std::string SHADER_NODE = "Shader";
    const std::string COLLECTION_SUFFIX = "_set";

    

    Scene * scene = NULL;
public:
    XmlScene();
    ~XmlScene();

    Scene * loadScene(const char* xmlSceneFile);
    bool saveScene(const Scene scene);

    
};

