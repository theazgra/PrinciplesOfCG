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
    //void getModelTransform(DrawableObject& object) const;
    void getModelTransform(Object& object) const;
    /*void setShader();
    void setModelMatrix(glm::mat4);*/

private:
    GLuint shaderProgram;
    GLint modelTransform;
    
};

