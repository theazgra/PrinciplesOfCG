#pragma once
#include <vector>

#include "Object.h"

class DrawableObject : public Object
{

private:
    void internalConstructor(std::vector<float>);

protected:
    DrawableObject();

    glm::mat4 objectMatrix;
    GLuint VAO, VBO, verticesCount;
    unsigned int shaderId;
    
public:
    DrawableObject(int);
    DrawableObject(int, std::vector<float>, int);
    ~DrawableObject();

    glm::mat4 getObjectMatrix() const;

    GLuint getVAO() const;
    GLuint getVerticesCount();
    unsigned int getShaderId() const;

    void resize(glm::vec3 resizeVector);
    void rotate(float, glm::vec3);
    void translate(glm::vec3);
    

};

