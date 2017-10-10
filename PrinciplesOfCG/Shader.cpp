#include "stdafx.h"
#include "Shader.h"




Shader::Shader(const char* vertex_shader_file, const char* fragment_shader_file)
{
    shaderProgram = loadShader(vertex_shader_file, fragment_shader_file);

    modelTransformMatrix = glGetUniformLocation(shaderProgram, "modelMatrix");
    viewMatrix = glGetUniformLocation(shaderProgram, "viewMatrix");
    projectionMatrix = glGetUniformLocation(shaderProgram, "projectionMatrix");
}

void Shader::useProgram() const 
{
    glUseProgram(shaderProgram);
}

void Shader::modelTransform(Object & object) const
{
    glUniformMatrix4fv(this->modelTransformMatrix, 1, GL_FALSE, &object.getObjectMatrix()[0][0]);
}

void Shader::applyCamera(glm::mat4 viewMat, glm::mat4 projectionMat) const
{
    glUniformMatrix4fv(this->viewMatrix, 1, GL_FALSE, &viewMat[0][0]);
    glUniformMatrix4fv(this->projectionMatrix, 1, GL_FALSE, &projectionMat[0][0]);
}

Shader::~Shader()
{
    deleteShader();
    shaderProgram = 0;
}

