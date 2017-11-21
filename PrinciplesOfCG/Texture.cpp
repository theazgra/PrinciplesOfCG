#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

GLuint Texture::loadTexture(const char * textureFile, unsigned int textureUnit)
{
    GLuint textureId = -1;
    int width, height;
    unsigned char * imgData = SOIL_load_image(
        textureFile,
        &width,
        &height,
        0,
        SOIL_LOAD_RGBA
    );
        
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        imgData
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(imgData);

    return textureId;
}
