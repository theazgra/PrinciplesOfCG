#pragma once

#include <stdexcpt.h>
#include <vector>

#include "Scene.h"
#include "Renderer.h"


class Application
{
private:
    Application();

    GLFWwindow*  window;
    std::vector<Scene*>* scenes;
    Renderer * renderer;
    Scene * currentScene;

public:
    static Application* getInstance();
    ~Application();

    void createScene(char*, Shader*);
    void renderCurrentScene();
    
    Scene & getCurrentScene();
    void setCurrentScene(char* sceneName);

    GLFWwindow& getWindow();

    void setRenderType(RenderType renderType);    
};

