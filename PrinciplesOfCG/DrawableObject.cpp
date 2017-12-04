#include "stdafx.h"
#include "DrawableObject.h"


DrawableObject::DrawableObject(int objectId, std::vector<float> vector, unsigned int shaderId, unsigned int textureId)
    : Object(objectId)
{
    this->textureId = textureId;
    this->shaderId = shaderId;
    this->objectMatrix = glm::mat4(1.0f);

    this->verticesCount = vector.size() / 3;
    size_t vecSize = vector.size() * sizeof(float);

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vecSize, vector.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)0);                     //position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));   //normals
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 6));   //UVs
}

DrawableObject::DrawableObject(int objectId, std::vector<AssimpVertex> data, std::vector<unsigned int> indices, unsigned int shaderId, unsigned int textureId)
{
    this->objectMatrix = glm::mat4(1.0f);
    this->shaderId = shaderId;
    this->textureId = textureId;
    this->VBO = 0;
    this->VAO = 0;
    this->IBO = 0;
    this->hasIndicesBuffer = true;

    this->indices = indices;

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    //glEnableVertexAttribArray(4);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(AssimpVertex) * data.size(), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpVertex), (GLvoid*)0);                     //position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpVertex), (GLvoid*)(sizeof(float) * 3));   //normals
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AssimpVertex), (GLvoid*)(sizeof(float) * 6));   //UVs
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpVertex), (GLvoid*)(sizeof(float) * 8));   //tangens

    //indices
    glGenBuffers(1, &this->IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

    this->verticesCount = data.size() * 3;
}

DrawableObject::DrawableObject(int objectId) : Object(objectId)
{
}


DrawableObject::DrawableObject()
{
}


GLuint DrawableObject::getVerticesCount()
{
    return this->verticesCount;
}

DrawableObject::~DrawableObject()
{
    this->VAO = 0;
    this->VBO = 0;
}

GLuint DrawableObject::getVAO() const
{
    return this->VAO;
}

void DrawableObject::resize(glm::vec3 resizeVector)
{
    this->objectMatrix = glm::scale(this->objectMatrix, resizeVector);
}

unsigned int DrawableObject::getShaderId() const
{
    return this->shaderId;
}

unsigned int DrawableObject::getTextureId() const
{
    return this->textureId;
}

void DrawableObject::rotate(float angle, glm::vec3 axis)
{
    objectMatrix = glm::rotate(objectMatrix, angle, axis);
}

void DrawableObject::translate(glm::vec3 translateVector)
{
    objectMatrix = glm::translate(objectMatrix, translateVector);
}

void DrawableObject::setPosition(glm::vec3 position)
{
    this->objectMatrix[0][3] = position.x;
    this->objectMatrix[1][3] = position.y;
    this->objectMatrix[2][3] = position.z;
}

bool DrawableObject::hasIndices()
{
    return this->hasIndicesBuffer;
}

std::vector<unsigned int> DrawableObject::getIndices() const
{
    return this->indices;
}

unsigned int DrawableObject::getIndicesCount() const
{
    return this->indices.size();
}

GLuint DrawableObject::getIBO() const
{
    return this->IBO;
}

void DrawableObject::setIsSkyBox(bool value)
{
    this->skyBox = value;
}

bool DrawableObject::isSkyBox() const
{
    return this->skyBox;
}

glm::mat4 DrawableObject::getObjectMatrix() const
{
    return objectMatrix;
}