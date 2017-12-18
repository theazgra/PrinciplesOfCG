#pragma once
#define REPORT_FRAME_TIME 0
#include "Scene.h"
#include "LightStruct.h"

class Renderer
{
private:
    GLFWwindow* window;
    void renderObject(DrawableObject&);
    void renderDrawableObjects(Scene &);
    void reportRenderTime();

    void shadowPass(Scene & scene);

    double lastRenderTime;
    unsigned int frameCount;
    unsigned int lastShaderId = -1;

    GLuint shadowFrameBuffer; 
    GLuint depthTexture;
    
    glm::mat4 depthMVP;
    glm::mat4 depthVP;
    glm::mat4 offsetMatrix;
public:
    Renderer(GLFWwindow&);
    ~Renderer();
    void renderScene(Scene &);

};

