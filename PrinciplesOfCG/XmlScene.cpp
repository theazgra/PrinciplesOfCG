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

    for (xml_node shaderNode : shaders.children(SHADER_NODE.c_str()))
    {
        //If id is not found basic shader is used.
        unsigned int shaderId = shaderNode.attribute("Id").as_uint(basicShaderId);
        bool shadowShader = fromXmlBool(shaderNode.child_value("Shadow"));
        const char* vsFile = shaderNode.child_value("VS");
        const char* fsFile = shaderNode.child_value("FS");

        Shader * shader = new Shader(vsFile, fsFile);

        xml_node heightMap = shaderNode.child("HeightMapTexture");
        if (!heightMap.empty())
        {
            shader->setHeightMapTextureUnit(heightMap.text().as_int());
        }


        if (shadowShader)
            Application::getInstance()->addShadowShader(shader, shaderId);
        else
            Application::getInstance()->addShader(shader, shaderId);
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
        bool playerCam = camera.attribute("PlayerCamera").as_bool();
        scene->addCamera(worldPos, targetPos, playerCam);
        scene->setActiveCamera(scene->getCameras().at(scene->getCameras().size() - 1)->getObjectId());
    }



    //Objects
    //TODO: Transformations.
    xml_node objects = root.child((OBJECT_NODE + SET_SUFFIX).c_str());
    for (xml_node object : objects.children(OBJECT_NODE.c_str()))
    {
        bool skybox = object.attribute("SkyBox").as_bool();
        const char* objFile = object.child_value("ObjFile");

        unsigned int shaderId = object.child("ShaderId").text().as_uint(basicShaderId);
        unsigned int textureId = object.child("TextureId").text().as_uint();
        unsigned int normalTextureId = object.child("NormalTextureId").text().as_int(-1);
        
        bool destructable = object.attribute("destructable").as_bool();
        bool crosshair = object.attribute("Crosshair").as_bool();
                                                           
        DrawableObject * drawableObj;
        if ((std::string)objFile == "Plain")
        {
            drawableObj = ObjectFactory::createPlain(nextId(), shaderId, textureId);
        }
        else
            drawableObj = ObjectFactory::createAssimpObject(objFile, nextId(), shaderId, textureId);

        drawableObj->setDestructable(destructable);
        drawableObj->setCrosshair(crosshair);

        

        xml_node moveOnCurveNode = object.child("MoveOnCurve");
        if (!moveOnCurveNode.empty())
        {
            float t_increment = moveOnCurveNode.attribute("t_increment").as_float(0.05);
            drawableObj->initializeBezierCurve(
                fromXmlVec3(moveOnCurveNode.child("P1")),
                fromXmlVec3(moveOnCurveNode.child("P2")),
                fromXmlVec3(moveOnCurveNode.child("P3")),
                fromXmlVec3(moveOnCurveNode.child("P4")),
                t_increment
            );
        }

        xml_node transformation = object.child("Transformation");                
        if (!transformation.empty())
        {
            xml_node scaling = transformation.child("Scale");
            if (!scaling.empty())
            {
                glm::vec3 scaleVector = fromXmlVec3(scaling);
                drawableObj->resize(scaleVector);
            }

            xml_node translation = transformation.child("Translate");
            if (!translation.empty())
            {
                glm::vec3 translateVector = fromXmlVec3(translation);
                drawableObj->translate(translateVector);
            }

            xml_node rotation = transformation.child("Rotate");
            if (!rotation.empty())
            {
                glm::vec3 rotateVector = fromXmlVec3(rotation);
                float angle = fromXmlFloat(rotation, "angle");
                drawableObj->rotate(angle, rotateVector);
            }

        }

        if (normalTextureId != -1)
            drawableObj->setNormalTextureId(normalTextureId);

        if (skybox)
        {
            scene->addSkyBox(drawableObj);
        }
        else
        {

            if (!object.child("ObjMatrix").empty())
            {
                drawableObj->setObjectMatrix(fromXmlMat4(object.child("ObjMatrix")));
            }
            
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
        
        xml_node powerNode = light.child("Power");
        xml_node ambientCoeffNode = light.child("AmbientCoefficient");
        xml_node specularCoeffNode = light.child("SpecularCoefficient");
        xml_node constFallOffNode = light.child("ConstatFallOff");
        xml_node linearFalOffNode = light.child("LinearFallOff");
        xml_node quadraticFallOffNode = light.child("QuadraticFallOff");
        
            

        if ((std::string)type == "P")
        {
            PointLight * pointLight = ObjectFactory::createPointLight(nextId(), intensity);
            glm::vec3 worldPos = fromXmlVec3(light.child("WorldPosition"));
            pointLight->move(worldPos);

            setAdditionalLightParameters(pointLight, powerNode, ambientCoeffNode, specularCoeffNode);
            setPointLightFalloff(pointLight, constFallOffNode, linearFalOffNode, quadraticFallOffNode);

            scene->addLight(pointLight);
        }
        else if ((std::string)type == "S")
        {
            glm::vec3 worldPos = fromXmlVec3(light.child("WorldPosition"));
            glm::vec3 direction = fromXmlVec3(light.child("Direction"));
            float innerCutOff = light.child("CutOff").attribute("Inner").as_float();
            float outerCutOff = light.child("CutOff").attribute("Outer").as_float();

            SpotLight * spotLight = ObjectFactory::createSpotLight(nextId(), intensity, innerCutOff, outerCutOff, direction);
            spotLight->move(worldPos);
            setAdditionalLightParameters(spotLight, powerNode, ambientCoeffNode, specularCoeffNode);
            setSpotLightFalloff(spotLight, constFallOffNode, linearFalOffNode, quadraticFallOffNode);

            xml_node cutOffNode = light.child("CutOff");
            xml_node outerCutOffNode = light.child("OuterCutOff");
            
            if (!cutOffNode.empty())
                spotLight->setCutOff(cutOffNode.text().as_float());
            if (!outerCutOffNode.empty())
                spotLight->setOuterCutOff(outerCutOffNode.text().as_float());

            if (shadowProducingLight)
                scene->addShadowLight(spotLight);
            else
                scene->addLight(spotLight);
        }
        else if ((std::string)type == "D")
        {
            glm::vec3 direction = fromXmlVec3(light.child("Direction"));
            DirectionalLight * dirLight = ObjectFactory::createDirectionalLight(nextId(), intensity, direction);
            setAdditionalLightParameters(dirLight, powerNode, ambientCoeffNode, specularCoeffNode);

            if (shadowProducingLight)
                scene->addShadowLight(dirLight);
            else
                scene->addLight(dirLight);
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

    //ligts
    xml_node lights = root.child((LIGHT_NODE + SET_SUFFIX).c_str());
    while (lights.remove_child(LIGHT_NODE.c_str()));

    for (Light * light : scene.getLights())
    {
        LightStruct lightInfo = light->getLightInfo();
        xml_node lightNode = lights.append_child(LIGHT_NODE.c_str());

        if (scene.getShadowLight()->getObjectId() == light->getObjectId())
            lightNode.append_attribute("Shadow").set_value(toXmlBool(true));


        if (lightInfo.lightType == SPOT_LIGHT)
            lightNode.append_attribute("Type").set_value("S");
        else if (lightInfo.lightType == POINT_LIGHT)
            lightNode.append_attribute("Type").set_value("P");
        else if (lightInfo.lightType == DIRECTIONAL_LIGHT)
            lightNode.append_attribute("Type").set_value("D");

        toXmlLightInfo(lightInfo, lightNode);
       
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

void XmlScene::setAdditionalLightParameters(Light * light, pugi::xml_node powerNode, pugi::xml_node ambientCoeffNode, pugi::xml_node specularCoeffNode)
{
    if (!powerNode.empty())
        light->setPower(powerNode.text().as_float());
    if (!ambientCoeffNode.empty())
        light->setAmbientStrength(ambientCoeffNode.text().as_float());
    if (!specularCoeffNode.empty())
        light->setSpeculatStrength(specularCoeffNode.text().as_float());
}

void XmlScene::setPointLightFalloff(PointLight * pointLight, pugi::xml_node constFallOffNode, pugi::xml_node linearFalOffNode, pugi::xml_node quadraticFallOfNode)
{
    if (!constFallOffNode.empty())
        pointLight->setConstantFallof(constFallOffNode.text().as_float());
    if (!linearFalOffNode.empty())
        pointLight->setLinearFallof(linearFalOffNode.text().as_float());
    if (!quadraticFallOfNode.empty())
        pointLight->setQuadraticFallof(quadraticFallOfNode.text().as_float());
}

void XmlScene::setSpotLightFalloff(SpotLight * spotLight, pugi::xml_node constFallOffNode, pugi::xml_node linearFalOffNode, pugi::xml_node quadraticFallOfNode)
{
    if (!constFallOffNode.empty())
        spotLight->setConstantFallof(constFallOffNode.text().as_float());
    if (!linearFalOffNode.empty())
        spotLight->setLinearFallof(linearFalOffNode.text().as_float());
    if (!quadraticFallOfNode.empty())
        spotLight->setQuadraticFallof(quadraticFallOfNode.text().as_float());
}

void XmlScene::toXmlLightInfo(LightStruct lightInfo, pugi::xml_node lightNode)
{
    toXmlVec3(lightNode.append_child("Intensity"), lightInfo.lightColor);
    toXmlVec3(lightNode.append_child("WorldPosition"), lightInfo.position);
    
    if (lightInfo.lightType != POINT_LIGHT)
        toXmlVec3(lightNode.append_child("Direction"), lightInfo.direction);

    lightNode.append_child("Power").text().set(lightInfo.power);
    lightNode.append_child("AmbientCoefficient").text().set(lightInfo.ambientStrength);
    lightNode.append_child("SpecularCoefficient").text().set(lightInfo.specularStrength);

    if (lightInfo.lightType != DIRECTIONAL_LIGHT)
    {
        lightNode.append_child("ConstatFallOff").text().set(lightInfo.constantFallOff);
        lightNode.append_child("LinearFallOff").text().set(lightInfo.linearFallOff);
        lightNode.append_child("QuadraticFallOff").text().set(lightInfo.quadraticFallOff);

        if (lightInfo.lightType == SPOT_LIGHT) 
        {
            lightNode.append_child("CutOff").text().set(lightInfo.cutOff);
            lightNode.append_child("OuterCutOff").text().set(lightInfo.outerCutOff);
        }
    }
}

glm::vec3 XmlScene::fromXmlVec3(pugi::xml_node node)
{
    if (!node.attribute("all").empty())
    {
        float val = node.attribute("all").as_float();
        return glm::vec3(val, val, val);
    }

    return glm::vec3(
        node.attribute("x").as_float(),
        node.attribute("y").as_float(),
        node.attribute("z").as_float()
    );
}

float XmlScene::fromXmlFloat(pugi::xml_node node, const pugi::char_t* attrName)
{
    return node.attribute(attrName).as_float();
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
            matrix[j][i] = values.at(++k);
        }
    }

    return matrix;
}

std::string XmlScene::toXmlMat4(glm::mat4 objMatrix)
{
    std::string strMatrix;

    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            std::string num = std::to_string(objMatrix[j][i]);
            strMatrix += num + ';';
        }
    }
    return (char*)strMatrix.c_str();
}

unsigned int XmlScene::nextId()
{
    return Application::getInstance()->getNextId();
}


