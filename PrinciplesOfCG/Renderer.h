#pragma once

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
    void renderDrawableObjects(Scene const&);
    void reportRenderTime();

    double lastRenderTime;
    unsigned int frameCount;
    unsigned int lastShaderId = -1;
    RenderType renderType;
public:
    Renderer(GLFWwindow&, RenderType);
    ~Renderer();
    void renderScene(Scene const&);
    void setRenderType(RenderType);

};

