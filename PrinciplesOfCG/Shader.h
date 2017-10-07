#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <stdexcpt.h>

#include "ShaderLoader.h"
#include "Object.h"

class Shader : ShaderLoader
{
public:
    Shader(const char* vertex_shader_file, const char* fragment_shader_file);
    ~Shader();

    void useProgram() const;
    void modelTransform(Object& object) const;

private:
    GLuint shaderProgram;
    GLuint modelTransformMatrix;
};

