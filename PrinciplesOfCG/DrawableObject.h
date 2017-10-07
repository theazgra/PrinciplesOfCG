#pragma once
#include <GL\glew.h>
#include <vector>

#include "Object.h"
#include "Shader.h"

class DrawableObject : public Object
{

private:
    GLuint VAO, VBO, verticesCount;
    Shader* shader = NULL;

    void internalConstructor(std::vector<float>);

public:
    DrawableObject(int, std::vector<float>);
    DrawableObject(int, std::vector<float>, Shader*);
    ~DrawableObject();

    GLuint getVAO() const;
    GLuint getVerticesCount();
    void resize(glm::vec3 resizeVector);
    Shader& getShader();
    bool hasOwnShader();

};

