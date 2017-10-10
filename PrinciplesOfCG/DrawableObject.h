#pragma once
#include <vector>

#include "Object.h"

class DrawableObject : public Object
{

private:
    GLuint VAO, VBO, verticesCount;
    unsigned int shaderId;

    void internalConstructor(std::vector<float>);

public:
    DrawableObject(int, std::vector<float>, int);
    ~DrawableObject();

    GLuint getVAO() const;
    GLuint getVerticesCount();
    unsigned int getShaderId() const;
    void resize(glm::vec3 resizeVector);
    

};

