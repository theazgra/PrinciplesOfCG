#include "stdafx.h"
#include "PlainObject.h"


PlainObject::PlainObject(int objectId, int shaderId) : DrawableObject(objectId)
{
    this->shaderId = shaderId;
    this->VBO = 0;
    this->VAO = 0;

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glBindVertexArray(0);

    this->verticesCount = 6;
}


PlainObject::~PlainObject()
{
}
