#pragma once
#include <glm\glm.hpp>
#include <stdexcpt.h>
#include <map>
#include <string>

#include "ShaderLoader.h"
#include "DrawableObject.h"
#include "LightStruct.h"


class Shader : ShaderLoader
{
private:
    GLuint shaderProgram;

    GLuint modelTransformMatrix;
    GLuint viewMatrix;
    GLuint projectionMatrix;
    GLuint cameraPositionPtr;
    
    GLuint lightPositionPtr;
    GLuint lightIntensityPtr;
    GLuint lightAmbientPtr;
    GLuint lightPowerPtr;

    GLuint lightCount;

    GLuint textureCoordPtr;

    glm::mat4 cameraViewMatrix;
    glm::mat4 cameraProjectionMatrix;
    glm::vec3 cameraPosition;

    glm::vec3 lightPosition;
    glm::vec3 lightIntensity;
    glm::vec3 lightAmbient;

    glm::vec2 textureCoord;

    std::map<GLuint, LightStruct> lights;
public:
    Shader();
    Shader(const char* vertex_shader_file, const char* fragment_shader_file);

    ~Shader();

    void useProgram() const;
    void modelTransform(DrawableObject& object) const;
    void applyCamera() const;
    void applyLight() const;
    void applyTexture(unsigned int textureUnit = 0) const;

    void setCameraMatrices(glm::mat4, glm::mat4, glm::vec3); 
    void setLightParameters(unsigned int lightId, LightStruct lightInfo);    
};

