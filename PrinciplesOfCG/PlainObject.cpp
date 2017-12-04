#include "stdafx.h"
#include "PlainObject.h"


PlainObject::PlainObject(int objectId, int shaderId, int textureId) : DrawableObject(objectId)
{
    this->shaderId = shaderId;
    this->textureId = textureId;
    this->VBO = 0;
    this->VAO = 0;

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plain2), plain2, GL_STATIC_DRAW);  

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(6 * sizeof(float)));
    glBindVertexArray(0);

    this->verticesCount = 6;
}


PlainObject::~PlainObject()
{
}
