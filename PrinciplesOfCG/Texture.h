#pragma once
#include "GL\glew.h"
#include <SOIL2.h>

class Texture
{
public:
    Texture();
    ~Texture();

    GLuint loadTexture(const char* textureFile, unsigned int textureUnit);
    
};

