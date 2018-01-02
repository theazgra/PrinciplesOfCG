#pragma once

#include "Vertex.h"
#include "Object.h"

class DrawableObject : public Object
{

private:

protected:
    const char* objFile;
    DrawableObject();

    glm::mat4 objectMatrix;
    GLuint VAO; 
    GLuint VBO;
    GLuint IBO;
    GLuint verticesCount;
    
    unsigned int shaderId;
    unsigned int textureId;
    unsigned int normalTextureId = 0;
    
    std::vector<unsigned int> indices;
    bool hasIndicesBuffer = false;
    bool skyBox = false;

public:
    DrawableObject(int objectId);
    DrawableObject(int objectId, std::vector<float> data, unsigned int shaderId, unsigned int textureId);
    DrawableObject(int objectId, std::vector<AssimpVertex> data, std::vector<unsigned int> indices, unsigned int shaderId, unsigned int textureId);
    ~DrawableObject();

    glm::mat4 getObjectMatrix() const;

    GLuint getVAO() const;
    GLuint getVerticesCount();
    unsigned int getShaderId() const;
    unsigned int getTextureId() const;
    unsigned int getNormalTextureId() const;
    

    void resize(glm::vec3 resizeVector);
    void rotate(float, glm::vec3);
    void translate(glm::vec3);

    void setPosition(glm::vec3 position);

    bool hasIndices();
    std::vector<unsigned int> getIndices() const;
    unsigned int getIndicesCount() const;
    GLuint getIBO() const;

    void setIsSkyBox(bool value);
    bool isSkyBox() const;
    void setNormalTextureId(unsigned int normalTextureId);

    void setObjectMatrix(glm::mat4 objectMatrix);
    
    void setObjFile(const char* objFile);
    std::string getObjFile();

};

