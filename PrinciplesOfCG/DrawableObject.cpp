#include "stdafx.h"
#include "DrawableObject.h"


DrawableObject::DrawableObject(int objectId, std::vector<float> vector) : Object(objectId)
{
    internalConstructor(vector);
    //shader = NULL;
}



DrawableObject::DrawableObject(int objectId, std::vector<float> vector, Shader* shader) : Object(objectId)
{
    internalConstructor(vector);
    this->shader = shader;
}

void DrawableObject::internalConstructor(std::vector<float> vector)
{
    verticesCount = vector.size() / 3;
    size_t vecSize = vector.size() * sizeof(float);
    this->VBO = 0;
    glGenBuffers(1, &this->VBO); // generate the this->VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vecSize, vector.data(), GL_STATIC_DRAW);

    //vertex attribute object(VAO)
    this->VAO = 0;
    glGenVertexArrays(1, &this->VAO); //generate the this->VAO
    glBindVertexArray(this->VAO); //bind the this->VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}


GLuint DrawableObject::getVerticesCount()
{
    return this->verticesCount;
}

DrawableObject::~DrawableObject()
{
    if (shader != NULL)
    {
        delete shader;
    }
    shader = NULL;

    this->VAO = 0;
    this->VBO = 0;
}

GLuint DrawableObject::getVAO() const
{
    return this->VAO;
}

void DrawableObject::resize(glm::vec3 resizeVector)
{
    glm::mat4 resizeMatrix = glm::scale(resizeVector);
    setModelMatrix(getObjectMatrix() * resizeMatrix);
}

Shader & DrawableObject::getShader()
{
    return *shader;
}

bool DrawableObject::hasOwnShader()
{
    return shader != NULL;
}
