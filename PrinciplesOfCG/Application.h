#pragma once                

#include <stdexcpt.h>
#include <vector>

#include "Scene.h"
#include "Renderer.h"
#include "Texture.h"
#include "XmlScene.h"

class Application
{
private:
    Application();
    

    unsigned int nextObjectId = -1;

    GLFWwindow*  window;
    std::vector<Scene*> scenes;
    Renderer * renderer;
    Scene * currentScene;

    std::map<int, Shader*> shaders;
    std::vector<unsigned int> textures;
    unsigned int BASIC_SHADER_ID = 0;
    unsigned int SHADOW_SHADER_ID;


    
    bool enableLookingAroud = false;
    bool moveCamera = true;
    int keyClickCount = 0;

    void bindCallbacks();

    XmlScene xmlScene;
    //will be removed.
    void setUpBasicScene();
public:
    static Application* getInstance();
    ~Application();

    void createScene(char*, Camera*);
    void renderCurrentScene();

    Scene & getCurrentScene();
    void setCurrentScene(char* sceneName);

    GLFWwindow& getWindow();

    Shader const& getBasicShader() const;
    Shader * getShader(unsigned int);
    Shader * getShadowShader();
    unsigned int getBasicShaderId() const;
    unsigned int addShader(Shader*);
    unsigned int addShader(Shader*, unsigned int shaderId);
    unsigned int addShadowShader(Shader*);
    unsigned int addShadowShader(Shader*, unsigned int shaderId);
    unsigned int addTexture(const char* textureFile);
    unsigned int addTexture(const char* textureFile, unsigned int textureId);
    unsigned int addSkyBoxTexture(const char* x, const char* nx, const char* y, const char* ny, const char* z, const char* nz);
    unsigned int addSkyBoxTexture(const char* x, const char* nx, const char* y, const char* ny, const char* z, const char* nz, unsigned int textureId);
    

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void error_callback(int error, const char* description);
    void window_size_callback(GLFWwindow* window, int width, int height);
    void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    unsigned int getNextId();

    void loadScene(const char* xmlSceneFile);
};

