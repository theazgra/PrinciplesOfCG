#pragma once

#include <stdexcpt.h>
#include <vector>

#include "Scene.h"
#include "Renderer.h"
#include "Controller.h"

class Application
{
private:
    Application();

    GLFWwindow*  window;
    std::vector<Scene*>* scenes;
    Renderer * renderer;
    Scene * currentScene;
    Controller controller;

    void bindCallbacks();
public:
    static Application* getInstance();
    ~Application();

    void createScene(char*, Shader*, Camera*);
    void renderCurrentScene();
    
    Scene & getCurrentScene();
    void setCurrentScene(char* sceneName);

    GLFWwindow& getWindow();

    void setRenderType(RenderType renderType);    

    void moveCamera(Direction) const;
    void moveCameraAndEye(Direction) const;
    void lookAround(double, double) const;
    void swapCamera();
    void resetCamera() const;
};

