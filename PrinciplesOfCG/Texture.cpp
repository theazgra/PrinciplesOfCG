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

GLuint Texture::loadSkyBox(const char* x, const char* nx, const char* y, const char* ny, const char* z, const char* nz, unsigned int textureUnit)
{
    GLuint textureId = -1;
    int width, height;

    unsigned char * imgX = SOIL_load_image(
        x,
        &width,
        &height,
        0,
        SOIL_LOAD_RGBA
    );

    unsigned char * imgNX = SOIL_load_image(
        nx,
        &width,
        &height,
        0,
        SOIL_LOAD_RGBA
    );

    unsigned char * imgY = SOIL_load_image(
        y,
        &width,
        &height,
        0,
        SOIL_LOAD_RGBA
    );

    unsigned char * imgNY = SOIL_load_image(
        ny,
        &width,
        &height,
        0,
        SOIL_LOAD_RGBA
    );

    unsigned char * imgZ = SOIL_load_image(
        z,
        &width,
        &height,
        0,
        SOIL_LOAD_RGBA
    );

    unsigned char * imgNZ = SOIL_load_image(
        nz,
        &width,
        &height,
        0,
        SOIL_LOAD_RGBA
    );

    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, ..., img.ptr());

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgX);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgNX);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgY);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgNY);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgZ);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgNZ);

    //glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    SOIL_free_image_data(imgX);
    SOIL_free_image_data(imgNX);
    SOIL_free_image_data(imgY);
    SOIL_free_image_data(imgNY);
    SOIL_free_image_data(imgZ);
    SOIL_free_image_data(imgNZ);

    return textureId;
}
