#include "stdafx.h"
#include "SphereObject.h"


SphereObject::SphereObject(int objectId) : DrawableObject(objectId)
{
    this->VBO = 0;
    this->VAO = 0;
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0); //position
    glEnableVertexAttribArray(1); //normal
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)sizeof(VERTICES[0].Position));

    verticesCount = pocetPrvku;
}


SphereObject::~SphereObject()
{
}
