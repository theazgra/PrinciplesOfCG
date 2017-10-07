#include "stdafx.h"
#include "Shader.h"




Shader::Shader(const char* vertex_shader_file, const char* fragment_shader_file)
{
    shaderProgram = loadShader(vertex_shader_file, fragment_shader_file);
    modelTransformMatrix = glGetUniformLocation(shaderProgram, "ModelMatrix");
}

void Shader::useProgram() const 
{
    glUseProgram(shaderProgram);
}

//void Shader::getModelTransform(DrawableObject & object) const
void Shader::modelTransform(Object & object) const
{
    glUniformMatrix4fv(modelTransformMatrix, 1, GL_FALSE, &object.getObjectMatrix()[0][0]);
}

Shader::~Shader()
{
    deleteShader();
    shaderProgram = 0;
}

