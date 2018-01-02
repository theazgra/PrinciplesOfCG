#pragma once

#include <pugixml.hpp>
#include "ObjectFactory.h"




class XmlScene
{
private:
    const char* sceneFile;

    //pugi::xml_document document;
    const std::string ROOT_NODE = "Scene";
    const std::string TEXTURE_NODE = "Texture";
    const std::string OBJECT_NODE = "Object";
    const std::string CAMERA_NODE = "Camera";
    const std::string LIGHT_NODE = "Light";
    const std::string SHADER_NODE = "Shader";
    const std::string SET_SUFFIX = "_set";

    pugi::xml_document document;

    Scene * scene = NULL;
    bool fromXmlBool(const char* value);
    glm::vec3 fromXmlVec3(pugi::xml_node node);
    glm::mat4 fromXmlMat4(pugi::xml_node node);
    
    const char* toXmlBool(bool value);
    void toXmlVec3(pugi::xml_node node, glm::vec3 value);
    std::string toXmlMat4(glm::mat4);

    unsigned int nextId();
public:
    XmlScene();
    ~XmlScene();

    Scene * loadScene(const char* xmlSceneFile);
    bool saveScene(Scene & scene);


};

