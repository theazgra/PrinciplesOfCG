#pragma once
#define REPORT_FRAME_TIME 1
#include "Scene.h"

enum RenderType
{
    Quads,
    Triangles
};

class Renderer
{
private:
    GLFWwindow* window;
    void renderDrawableObjects(Scene &);
    void reportRenderTime();

    double lastRenderTime;
    unsigned int frameCount;
    unsigned int lastShaderId = -1;
    RenderType renderType;
public:
    Renderer(GLFWwindow&, RenderType);
    ~Renderer();
    void renderScene(Scene &);
    void setRenderType(RenderType);

};

