#include "stdafx.h"
#include "Shader.h"




Shader::Shader()
{
}

Shader::Shader(const char* vertex_shader_file, const char* fragment_shader_file)
{
    this->shaderProgram = loadShader(vertex_shader_file, fragment_shader_file);

    this->modelTransformMatrix = glGetUniformLocation(this->shaderProgram, "modelMatrix");
    this->viewMatrix = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    this->projectionMatrix = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
    this->cameraPositionPtr = glGetUniformLocation(this->shaderProgram, "cameraPosition");

    //this is how vec3 can be passed to vertex shader.
    this->lightPositionPtr = glGetUniformLocation(this->shaderProgram, "lightPosition");
    this->lightIntensityPtr = glGetUniformLocation(this->shaderProgram, "lightIntensity");
    this->lightAmbientPtr = glGetUniformLocation(this->shaderProgram, "lightAmbient");
    this->lightPowerPtr = glGetUniformLocation(this->shaderProgram, "lightPower");

    this->textureCoordPtr = glGetUniformLocation(this->shaderProgram, "textura");
    this->lightCount = glGetUniformLocation(this->shaderProgram, "lightCount");
    this->shadowTexturePtr = glGetUniformLocation(this->shaderProgram, "shadowMap");

    this->depthViewMatrix = glGetUniformLocation(this->shaderProgram, "depthViewMatrix");
    this->depthProjectionMatrix = glGetUniformLocation(this->shaderProgram, "depthProjectionMatrix");
    this->shadowVP = glGetUniformLocation(this->shaderProgram, "shadowVP");
    this->depthMVP = glGetUniformLocation(this->shaderProgram, "depthMVP");

    this->normalTexture = glGetUniformLocation(this->shaderProgram, "normalTexture");
    this->hasNormalTexture = glGetUniformLocation(this->shaderProgram, "hasNormalTexture");
}

void Shader::useProgram() const 
{
    glUseProgram(this->shaderProgram);
    glUniform1i(this->shadowTexturePtr, 0);
//    applyCamera();
//    applyLight();
}

void Shader::modelTransform(DrawableObject & object) const
{
    glUniformMatrix4fv(this->modelTransformMatrix, 1, GL_FALSE, &object.getObjectMatrix()[0][0]);            
}



void Shader::applyCamera() const
{
    glUniformMatrix4fv(this->viewMatrix, 1, GL_FALSE, &cameraViewMatrix[0][0]);
    glUniformMatrix4fv(this->projectionMatrix, 1, GL_FALSE, &cameraProjectionMatrix[0][0]);
    glUniform3f(this->cameraPositionPtr, this->cameraPosition.x, this->cameraPosition.y, this->cameraPosition.z);
}

void Shader::applyLight() const
{
    glUniform1i(this->lightCount, this->lights.size());
    int i = 0;
    for (std::pair<GLuint, LightStruct> pair : this->lights)
    {
        glUniform1ui(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].lightType").c_str()),
            pair.second.lightType);

        glUniform1f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].power").c_str()),
            pair.second.power);

        glUniform3f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].position").c_str()),
            pair.second.position.x,
            pair.second.position.y,
            pair.second.position.z);

        glUniform3f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].direction").c_str()),
            pair.second.direction.x,
            pair.second.direction.y,
            pair.second.direction.z);

        glUniform1f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].cutOff").c_str()),
            pair.second.cutOff);

        glUniform1f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].outerCutOff").c_str()),
            pair.second.outerCutOff);

        glUniform1f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].ambientStrength").c_str()),
            pair.second.ambientStrength);

        glUniform3f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].lightColor").c_str()),
            pair.second.lightColor.x,
            pair.second.lightColor.y,
            pair.second.lightColor.z);

        glUniform1f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].specularStrength").c_str()),
            pair.second.specularStrength);

        glUniform1f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].constant").c_str()),
            pair.second.constantFallOff);

        glUniform1f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].linear").c_str()),
            pair.second.linearFallOff);

        glUniform1f(glGetUniformLocation(this->shaderProgram, ("lights[" + std::to_string(i) + "].quadratic").c_str()),
            pair.second.quadraticFallOff);   

        ++i;
    }
}

void Shader::applyTexture(unsigned int textureUnit) const
{
    glUniform1i(this->textureCoordPtr, textureUnit);
}

void Shader::applyNormalTexture(unsigned int textureUnit) const
{
    glUniform1i(this->normalTexture, textureUnit);
    glUniform1i(this->hasNormalTexture, textureUnit != 0 ? 1 : 0);
}

void Shader::setCameraMatrices(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition)
{
    this->cameraViewMatrix = viewMatrix;
    this->cameraProjectionMatrix = projectionMatrix;
    this->cameraPosition = cameraPosition;
}

void Shader::setLightParameters(unsigned int lightId, LightStruct lightInfo)
{
    this->lights[lightId] = lightInfo;
}

void Shader::setDepthBiasMVP(glm::mat4 depthBiasMVP)
{
    glUniformMatrix4fv(this->shadowVP, 1, GL_FALSE, &depthBiasMVP[0][0]);
}

void Shader::setDepthMVP(glm::mat4 depthMVP)
{
    glUniformMatrix4fv(this->depthMVP, 1, GL_FALSE, &depthMVP[0][0]);
}

void Shader::setDepthVP(glm::mat4 depthVP)
{
    glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, "depthVP"), 1, GL_FALSE, &depthVP[0][0]);
}

Shader::~Shader()
{
    deleteShader();
    shaderProgram = 0;
}

