#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <stdexcpt.h>

#include "ShaderLoader.h"
#include "Object.h"
#include "Camera.h"
#include "Observer.h"

class Shader : ShaderLoader, public Observer
{
private:
    GLuint shaderProgram;

    GLuint modelTransformMatrix;
    GLuint viewMatrix;
    GLuint projectionMatrix;

    glm::mat4 cameraViewMatrix;
    glm::mat4 cameraProjectionMatrix;

    Camera* camera;

public:
    Shader();
    Shader(const char* vertex_shader_file, const char* fragment_shader_file);
    ~Shader();

    void useProgram() const;
    void modelTransform(Object& object) const;
    void applyCamera() const;

    void setCamera(Camera*);
    void notify() override;


};

