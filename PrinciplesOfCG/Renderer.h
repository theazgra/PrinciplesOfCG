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
    void reportFPS();

    double lastRenderTime;
    int frames;
    RenderType renderType;
public:
    Renderer(GLFWwindow&, RenderType);
    ~Renderer();
    void renderScene(Scene const&);
    void setRenderType(RenderType);

};

