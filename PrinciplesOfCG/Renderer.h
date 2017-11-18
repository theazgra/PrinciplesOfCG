#pragma once
#define REPORT_FRAME_TIME 0
#include "Scene.h"

class Renderer
{
private:
    GLFWwindow* window;
    void renderDrawableObjects(Scene &);
    void reportRenderTime();

    double lastRenderTime;
    unsigned int frameCount;
    unsigned int lastShaderId = -1;
public:
    Renderer(GLFWwindow&);
    ~Renderer();
    void renderScene(Scene &);

};

