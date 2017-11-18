#pragma once

#include "Vertex.h"
#include "Object.h"

class DrawableObject : public Object
{

private:

protected:
    DrawableObject();

    glm::mat4 objectMatrix;
    GLuint VAO; 
    GLuint VBO;
    GLuint IBO;
    GLuint verticesCount;
    
    unsigned int shaderId;
    unsigned int textureId;
    
    std::vector<unsigned int> indices;
    bool hasIndicesBuffer = false;

public:
    DrawableObject(int objectId);
    DrawableObject(int objectId, std::vector<float> data, unsigned int shaderId, unsigned int textureId);
    DrawableObject(int objectId, std::vector<AssimpVertex> data, unsigned int shaderId, unsigned int textureId);
    ~DrawableObject();

    glm::mat4 getObjectMatrix() const;

    GLuint getVAO() const;
    GLuint getVerticesCount();
    unsigned int getShaderId() const;

    void resize(glm::vec3 resizeVector);
    void rotate(float, glm::vec3);
    void translate(glm::vec3);

    bool hasIndices();
    std::vector<unsigned int> getIndices() const;
    unsigned int getIndicesCount() const;
    GLuint getIBO() const;

};

