#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <stdexcpt.h>

#include "ShaderLoader.h"
#include "Object.h"
#include "Camera.h"

class Shader : ShaderLoader
{
private:
    GLuint shaderProgram;

    GLuint modelTransformMatrix;
    GLuint viewMatrix;
    GLuint projectionMatrix;

    Camera* cam;

public:
    Shader(const char* vertex_shader_file, const char* fragment_shader_file);
    ~Shader();

    void useProgram() const;
    void modelTransform(Object& object) const;
    void applyCamera(glm::mat4, glm::mat4) const;


};

