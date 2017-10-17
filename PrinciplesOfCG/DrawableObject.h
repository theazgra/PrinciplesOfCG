#pragma once
#include <vector>

#include "Object.h"

class DrawableObject : public Object
{

private:
    void internalConstructor(std::vector<float>);

protected:
    GLuint VAO, VBO, verticesCount;
    unsigned int shaderId;

public:
    DrawableObject(int);
    DrawableObject(int, std::vector<float>, int);
    ~DrawableObject();

    GLuint getVAO() const;
    GLuint getVerticesCount();
    unsigned int getShaderId() const;
    void resize(glm::vec3 resizeVector);
    

};

