#include "stdafx.h"
#include "DrawableObject.h"


DrawableObject::DrawableObject(int objectId, std::vector<float> vector, int shaderId) : Object(objectId)
{
    this->objectMatrix = glm::mat4(1.0f);
    internalConstructor(vector);
    this->shaderId = shaderId;
}

DrawableObject::DrawableObject(int objectId) : Object(objectId)
{
}

//DrawableObject::DrawableObject(int objectId, float ** vertices, int shaderId, int verticiesCount) : Object(objectId)
//{
//    this->objectMatrix = glm::mat4(1.0f);
//    this->shaderId = shaderId;
//    this->VBO = 0;
//    this->VAO = 0;
//
//    glGenVertexArrays(1, &this->VAO);
//    glBindVertexArray(this->VAO);
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    glEnableVertexAttribArray(2);
//
//    glGenBuffers(1, &this->VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(3 * sizeof(float)));
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(6 * sizeof(float)));
//    glBindVertexArray(0);
//
//    this->verticesCount = 6;
//}


void DrawableObject::internalConstructor(std::vector<float> vector)
{
    verticesCount = vector.size() / 3;
    size_t vecSize = vector.size() * sizeof(float);
    this->VBO = 0;
    glGenBuffers(1, &this->VBO); // generate the this->VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vecSize, vector.data(), GL_STATIC_DRAW);

    this->VAO = 0;
    glGenVertexArrays(1, &this->VAO); //generate the this->VAO
    glBindVertexArray(this->VAO); //bind the this->VAO
    glEnableVertexAttribArray(0); //position
    glEnableVertexAttribArray(1); //normal
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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
    //glm::scale(objectMatrix, resizeVector);
    this->objectMatrix = glm::scale(this->objectMatrix, resizeVector);
}

unsigned int DrawableObject::getShaderId() const
{
    return this->shaderId;
}

void DrawableObject::rotate(float angle, glm::vec3 axis)
{
    objectMatrix = glm::rotate(objectMatrix, angle, axis);
}

void DrawableObject::translate(glm::vec3 translateVector)
{
    objectMatrix = glm::translate(objectMatrix, translateVector);
}

glm::mat4 DrawableObject::getObjectMatrix() const
{
    return objectMatrix;
}