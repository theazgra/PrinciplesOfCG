#include "stdafx.h"
#include "DrawableObject.h"


DrawableObject::DrawableObject(int objectId, std::vector<float> vector, unsigned int shaderId, unsigned int textureId)
    : Object(objectId)
{
    this->worldPosition = glm::vec3(0, 0, 0);
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
    : Object(objectId)
{
    this->worldPosition = glm::vec3(0, 0, 0);
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
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpVertex), (GLvoid*)(sizeof(float) * 8));   //tangents

    //indices
    glGenBuffers(1, &this->IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

    this->verticesCount = data.size() * 3;
}

DrawableObject::DrawableObject(int objectId) : Object(objectId)
{
    this->worldPosition = glm::vec3(0, 0, 0);
}


DrawableObject::DrawableObject()
{
    this->worldPosition = glm::vec3(0, 0, 0);
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

unsigned int DrawableObject::getNormalTextureId() const
{
    return this->normalTextureId;
}

void DrawableObject::rotate(float angle, glm::vec3 axis)
{
    objectMatrix = glm::rotate(objectMatrix, angle, axis);
}

void DrawableObject::translate(glm::vec3 translateVector)
{
    this->worldPosition += translateVector;
    objectMatrix = glm::translate(objectMatrix, translateVector);
}

void DrawableObject::setDestructable(bool value)
{
    this->destructable = value;
}

void DrawableObject::setPosition(glm::vec3 position)
{
    this->objectMatrix[0][3] = position.x;
    this->objectMatrix[1][3] = position.y;
    this->objectMatrix[2][3] = position.z;

    printf("spirte");
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

bool DrawableObject::isDestructable() const
{
    if (this->skyBox)
        return false;

    return this->destructable;
}

bool DrawableObject::isCrosshair() const
{
    return this->crosshair;
}

bool DrawableObject::shouldBeDeleted() const
{
    return this->deleteObject;
}

glm::vec3 DrawableObject::getPosition() const
{
    return this->worldPosition;
    /*return glm::vec3(
        this->objectMatrix[0][3],
        this->objectMatrix[1][3],
        this->objectMatrix[2][3]
    );*/
}

void DrawableObject::setNormalTextureId(unsigned int normalTextureId)
{
    this->normalTextureId = normalTextureId;
}

void DrawableObject::setObjectMatrix(glm::mat4 objectMatrix)
{
    this->objectMatrix = objectMatrix;
}

void DrawableObject::setObjFile(const char * objFile)
{
    this->objFile = objFile;
}

void DrawableObject::setCrosshair(bool value)
{
    this->crosshair = value;
}

void DrawableObject::moveInDirection(glm::vec3 direction, int drawBeforeDelete)
{
    this->_moveInDirection = true;
    this->moveDirection = direction;
    this->drawCountBeforeDelete = drawBeforeDelete;
}

std::string DrawableObject::getObjFile()
{
    return this->objFile;
}

void DrawableObject::initializeBezierCurve(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float t_increment)
{
    bezierCurve.initialize(p1, p2, p3, p4, t_increment);
    moveOnCurve = true;
}

glm::mat4 DrawableObject::getObjectMatrix()
{
    if (moveOnCurve)
    {
        ++drawCounter;
        if (drawCounter >= 15 && bezierCurve)
        {
            drawCounter = 0;
            glm::vec3 objectPosition(this->objectMatrix[3]);
            glm::vec3 desiredPosition = bezierCurve.getPointOnCurve();

            glm::vec3 translateVector = desiredPosition - objectPosition;

            this->worldPosition += translateVector;
            this->translate(translateVector);
        }
        else if (!bezierCurve)
        {
            bezierCurve.reverse();
        }
    }
    else if (this->_moveInDirection)
    {
        ++this->drawCounter;
        this->worldPosition += this->moveDirection;
        this->translate(this->moveDirection);

        if (this->drawCounter >= this->drawCountBeforeDelete)
            this->deleteObject = true;
    }



    return objectMatrix;
}