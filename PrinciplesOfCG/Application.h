#pragma once

#include <stdexcpt.h>
#include <vector>

#include "Scene.h"
#include "Renderer.h"


class Application
{
public:
    static Application* getInstance();
    ~Application();

    void createScene(char*, Shader*);
    void renderCurrentScene();
    Scene & getCurrentScene();

    GLFWwindow& getWindow();

    void setRenderType(RenderType renderType);

private:
    Application();
    
    GLFWwindow*  window;
    std::vector<Scene*>* scenes;
    Renderer * renderer;
    Scene * currentScene;
    
    
    
};

