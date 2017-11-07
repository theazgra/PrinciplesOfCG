#pragma once
#include <glm\glm.hpp>
#include <stdexcpt.h>

#include "ShaderLoader.h"
#include "DrawableObject.h"
#include "Texture.h"

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

    GLuint textureCoordPtr;

    glm::mat4 cameraViewMatrix;
    glm::mat4 cameraProjectionMatrix;
    glm::vec3 cameraPosition;

    glm::vec3 lightPosition;
    glm::vec3 lightIntensity;
    glm::vec3 lightAmbient;

    glm::vec2 textureCoord;
    float lightPower;

public:
    Shader();
    Shader(const char* vertex_shader_file, const char* fragment_shader_file);
    //Shader(const char* vertex_shader_file, const char* fragment_shader_file, const char* texture_file);

    ~Shader();

    void useProgram() const;
    void modelTransform(DrawableObject& object) const;
    void applyCamera() const;
    void applyLight() const;
    void applyTexture() const;

    void setCameraMatrices(glm::mat4, glm::mat4, glm::vec3); 
    void setLightParameters(glm::vec3, glm::vec3, glm::vec3, float);
    void setTexture(char* textureFile);
};

