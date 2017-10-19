#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <stdexcpt.h>

#include "ShaderLoader.h"
#include "DrawableObject.h"

class Shader : ShaderLoader
{
private:
    GLuint shaderProgram;

    GLuint modelTransformMatrix;
    GLuint viewMatrix;
    GLuint projectionMatrix;
    
    GLuint lightPositionPtr;
    GLuint lightIntensityPtr;
    GLuint lightAmbientPtr;
    GLuint lightPowerPtr;

    glm::mat4 cameraViewMatrix;
    glm::mat4 cameraProjectionMatrix;

    glm::vec3 lightPosition;
    glm::vec3 lightIntensity;
    glm::vec3 lightAmbient;
    float lightPower;

public:
    Shader();
    Shader(const char* vertex_shader_file, const char* fragment_shader_file);
    ~Shader();

    void useProgram() const;
    void modelTransform(DrawableObject& object) const;
    void applyCamera() const;
    void applyLight() const;

    void setCameraMatrices(glm::mat4, glm::mat4); 
    void setLightParameters(glm::vec3, glm::vec3, glm::vec3, float);
};

