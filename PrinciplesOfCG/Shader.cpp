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
}

Shader::Shader(const char * vertex_shader_file, const char * fragment_shader_file, const char * texture_file)
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

    setTexture(texture_file);
    this->hasTexture = true;
}

void Shader::useProgram() const 
{
    glUseProgram(this->shaderProgram);
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
    glUniform3f(this->lightPositionPtr, this->lightPosition[0], this->lightPosition[1], this->lightPosition[2]);
    glUniform3f(this->lightIntensityPtr, this->lightIntensity[0], this->lightIntensity[1], this->lightIntensity[2]);
    glUniform3f(this->lightAmbientPtr, this->lightAmbient[0], this->lightAmbient[1], this->lightAmbient[2]);
    glUniform1f(this->lightPowerPtr, this->lightPower);
}

void Shader::applyTexture() const
{
    if (this->hasTexture)
        glUniform1i(this->textureCoordPtr, 0);
    //glUniform1i(glGetUniformLocation(this->shaderProgram, "textura"), 0);
}

void Shader::setCameraMatrices(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition)
{
    this->cameraViewMatrix = viewMatrix;
    this->cameraProjectionMatrix = projectionMatrix;
    this->cameraPosition = cameraPosition;
}

void Shader::setLightParameters(glm::vec3 worldPosition, glm::vec3 lightIntensity, glm::vec3 ambient, float lightPower)
{
    this->lightPosition = worldPosition;
    this->lightIntensity = lightIntensity;
    this->lightAmbient = ambient;
    this->lightPower = lightPower;
}

void Shader::setTexture(const char * textureFile)
{
    Texture tex;
    tex.loadTexture(textureFile);
}

Shader::~Shader()
{
    deleteShader();
    shaderProgram = 0;
}

