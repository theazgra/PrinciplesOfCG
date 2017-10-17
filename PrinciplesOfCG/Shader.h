#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <stdexcpt.h>

#include "ShaderLoader.h"
#include "Object.h"
#include "CameraObserver.h"

class Shader : ShaderLoader, public CameraObserver
{
private:
    GLuint shaderProgram;

    GLuint modelTransformMatrix;
    GLuint viewMatrix;
    GLuint projectionMatrix;

    glm::mat4 cameraViewMatrix;
    glm::mat4 cameraProjectionMatrix;

public:
    Shader();
    Shader(const char* vertex_shader_file, const char* fragment_shader_file);
    ~Shader();

    void useProgram() const;
    void modelTransform(Object& object) const;
    void applyCamera() const;

    void notify(glm::mat4, glm::mat4) override;
 
};

