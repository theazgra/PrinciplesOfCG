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

    double lastXPosition = 0;
    double lastYPosition = 0;
    bool enableLookingAroud = false;
    int mouseChange = 0;

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

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void error_callback(int error, const char* description);
    void window_size_callback(GLFWwindow* window, int width, int height);
    void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

