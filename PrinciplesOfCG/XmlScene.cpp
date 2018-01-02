#include "stdafx.h"
#include "XmlScene.h"
#include "Application.h"



XmlScene::XmlScene()
{
}

XmlScene::~XmlScene()
{
}

Scene * XmlScene::loadScene(const char * xmlSceneFile)
{
    sceneFile = xmlSceneFile;
    using namespace pugi;

    xml_parse_result result = document.load_file(xmlSceneFile);
    if (!result)
    {
        std::string errorMsg = "Couldn't load scene from xml file. Description: " + (std::string)result.description();
        throw new std::exception(errorMsg.c_str());
    }
    xml_node root = document.child(ROOT_NODE.c_str());
    const char* sceneName = root.attribute("Name").as_string();

    Scene * scene = new Scene(sceneName);

    //Shaders
    xml_node shaders = root.child((SHADER_NODE + SET_SUFFIX).c_str());

    unsigned int basicShaderId = Application::getInstance()->getBasicShaderId();

    for (xml_node shader : shaders.children(SHADER_NODE.c_str()))
    {
        //If id is not found basic shader is used.
        unsigned int shaderId = shader.attribute("Id").as_uint(basicShaderId);
        bool shadowShader = fromXmlBool(shader.child_value("Shadow"));
        const char* vsFile = shader.child_value("VS");
        const char* fsFile = shader.child_value("FS");

        if (shadowShader)
            Application::getInstance()->addShadowShader(new Shader(vsFile, fsFile), shaderId);
        else
            Application::getInstance()->addShader(new Shader(vsFile, fsFile), shaderId);
    }

    //Textures
    xml_node textures = root.child((TEXTURE_NODE + SET_SUFFIX).c_str());
    for (xml_node texture : textures.children(TEXTURE_NODE.c_str()))
    {
        bool skybox = texture.attribute("CubeMap").as_bool();
        unsigned int textureId = texture.attribute("Id").as_uint();
        if (skybox)
        {
            const char* PosX = texture.child_value("PosX");
            const char* NegX = texture.child_value("NegX");
            const char* PosY = texture.child_value("PosY");
            const char* NegY = texture.child_value("NegY");
            const char* PosZ = texture.child_value("PosZ");
            const char* NegZ = texture.child_value("NegZ");
            Application::getInstance()->addSkyBoxTexture(PosX, NegX, PosY, NegY, PosZ, NegZ, textureId);
        }
        else
        {
            const char* texFile = texture.child_value("Image");
            Application::getInstance()->addTexture(texFile, textureId);
        }
    }

    //Cameras
    xml_node cameras = root.child((CAMERA_NODE + SET_SUFFIX).c_str());
    for (xml_node camera : cameras.children(CAMERA_NODE.c_str()))
    {
        glm::vec3 worldPos = fromXmlVec3(camera.child("WorldPosition"));
        glm::vec3 targetPos = fromXmlVec3(camera.child("TargetPosition"));
        scene->addCamera(worldPos, targetPos);
        scene->setActiveCamera(scene->getCameras().at(scene->getCameras().size() - 1)->getObjectId());
    }



    //Objects
    xml_node objects = root.child((OBJECT_NODE + SET_SUFFIX).c_str());
    for (xml_node object : objects.children(OBJECT_NODE.c_str()))
    {
        bool skybox = object.attribute("SkyBox").as_bool();
        glm::mat4 objMatrix = fromXmlMat4(object.child("ObjMatrix"));
        unsigned int shaderId = object.child("ShaderId").text().as_uint(basicShaderId);
        unsigned int textureId = object.child("TextureId").text().as_uint();
        unsigned int normalTextureId = object.child("NormalTextureId").text().as_int(-1);
        const char* objFile = object.child_value("ObjFile");

        DrawableObject * drawableObj;
        if ((std::string)objFile == "Plain")
        {
            drawableObj = ObjectFactory::createPlain(nextId(), shaderId, textureId);
        }
        else
            drawableObj = ObjectFactory::createAssimpObject(objFile, nextId(), shaderId, textureId);

        if (normalTextureId != -1)
            drawableObj->setNormalTextureId(normalTextureId);

        if (skybox)
        {
            scene->addSkyBox(drawableObj);
        }
        else
        {
            if (drawableObj->getTextureId() == 1)
            {
                int id = drawableObj->getObjectId();
                int basoc = id;

            }
            drawableObj->setObjectMatrix(objMatrix);
            scene->addDrawableObject(drawableObj);
        }
    }

    //Lights
    xml_node lights = root.child((LIGHT_NODE + SET_SUFFIX).c_str());
    for (xml_node light : lights.children(LIGHT_NODE.c_str()))
    {
        const char* type = light.attribute("Type").as_string();
        bool shadowProducingLight = light.attribute("Shadow").as_bool();

        glm::vec3 intensity = fromXmlVec3(light.child("Intensity"));

        if ((std::string)type == "P")
        {
            PointLight * pl = ObjectFactory::createPointLight(nextId(), intensity);
            glm::vec3 worldPos = fromXmlVec3(light.child("WorldPosition"));
            pl->move(worldPos);

            scene->addLight(pl);
        }
        else if ((std::string)type == "S")
        {
            glm::vec3 worldPos = fromXmlVec3(light.child("WorldPosition"));
            glm::vec3 direction = fromXmlVec3(light.child("Direction"));
            float innerCutOff = light.child("CutOff").attribute("Inner").as_float();
            float outerCutOff = light.child("CutOff").attribute("Outer").as_float();

            SpotLight * sl = ObjectFactory::createSpotLight(nextId(), intensity, innerCutOff, outerCutOff, direction);
            sl->move(worldPos);

            if (shadowProducingLight)
                scene->addShadowLight(sl);
            else
                scene->addLight(sl);
        }
        else if ((std::string)type == "D")
        {
            glm::vec3 direction = fromXmlVec3(light.child("Direction"));
            DirectionalLight * dl = ObjectFactory::createDirectionalLight(nextId(), intensity, direction);

            if (shadowProducingLight)
                scene->addShadowLight(dl);
            else
                scene->addLight(dl);
        }
    }

    return scene;
}

bool XmlScene::saveScene(Scene & scene)
{
    //Shaders and textures does not need to be rewritten. Just objects, lights and cameras.
    using namespace pugi;
    bool result = true;

    xml_node root = document.child(ROOT_NODE.c_str());
    //cameras
    xml_node cameras = root.child((CAMERA_NODE + SET_SUFFIX).c_str());
    //remove old cameras...
    while (cameras.remove_child(CAMERA_NODE.c_str()));

    for (Camera * cam : scene.getCameras())
    {
        xml_node cameraNode = cameras.append_child(CAMERA_NODE.c_str());
        xml_node worldPos = cameraNode.append_child("WorldPosition");
        toXmlVec3(worldPos, cam->getWorldPosition());

        xml_node targetPos = cameraNode.append_child("TargetPosition");
        toXmlVec3(targetPos, cam->getTarget());
    }

    //Objects
    xml_node objects = root.child((OBJECT_NODE + SET_SUFFIX).c_str());
    while (objects.remove_child(OBJECT_NODE.c_str()));

    for (DrawableObject* obj : scene.getDrawableObjects())
    {
        xml_node objNode = objects.append_child(OBJECT_NODE.c_str());
        
        objNode.append_attribute("SkyBox").set_value(toXmlBool(obj->isSkyBox()));
        std::string objFile = obj->getObjFile();
        objNode.append_child("ObjFile").text().set(objFile.c_str());
        objNode.append_child("ShaderId").text().set(obj->getShaderId());
        objNode.append_child("TextureId").text().set(obj->getTextureId());
        
        if (obj->getNormalTextureId() != 0)
            objNode.append_child("NormalTextureId").text().set(obj->getNormalTextureId());

        std::string str = toXmlMat4(obj->getObjectMatrix());
        objNode.append_child("ObjMatrix").text().set(str.c_str());

    }




    result = document.save_file(sceneFile);
    return result;
}

bool XmlScene::fromXmlBool(const char* value)
{
    return ((std::string)value) == "True" ? true : false;
    
}

const char* XmlScene::toXmlBool(bool value)
{
    return (value ? "True" : "False");
}

void XmlScene::toXmlVec3(pugi::xml_node node, glm::vec3 value)
{
    node.append_attribute("x").set_value(value.x);
    node.append_attribute("y").set_value(value.y);
    node.append_attribute("z").set_value(value.z);
}

std::string XmlScene::toXmlMat4(glm::mat4 objMatrix)
{
    std::string strMatrix;

    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            std::string num = std::to_string(objMatrix[i][j]);
            strMatrix += num + ';';
            //strMatrix.append( num + ";");
        }
    }
    return (char*)strMatrix.c_str();
}

glm::vec3 XmlScene::fromXmlVec3(pugi::xml_node node)
{
    return glm::vec3(
        node.attribute("x").as_float(),
        node.attribute("y").as_float(),
        node.attribute("z").as_float()
    );
}

glm::mat4 XmlScene::fromXmlMat4(pugi::xml_node node)
{
    std::vector<float> values;
    std::string token;

    std::istringstream tokenStream(node.text().as_string());
    while (std::getline(tokenStream, token, ';'))
    {
        values.push_back(std::stof(token));
    }

    glm::mat4 matrix;

    int k = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            matrix[i][j] = values.at(++k);
        }
    }

    return matrix;
}

unsigned int XmlScene::nextId()
{
    return Application::getInstance()->getNextId();
}


