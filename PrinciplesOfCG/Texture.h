#pragma once
#include "GL\glew.h"
#include <SOIL2.h>

class Texture
{
public:
    Texture();
    ~Texture();

    GLuint loadTexture(const char* textureFile, unsigned int textureUnit);
    GLuint loadSkyBox(const char* x, const char* nx, const char* y, const char* ny, const char* z, const char* nz, unsigned int textureUnit);
    
};

