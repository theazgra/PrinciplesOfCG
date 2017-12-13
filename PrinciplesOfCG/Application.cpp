#include "stdafx.h"
#include "Application.h"

static Application* instance;

GLFWwindow & Application::getWindow()
{
    return *window;
}

Application::Application()
{

    if (!glfwInit())
    {
        fprintf(stderr, "Could not init GLFW");
        throw std::exception("Could not init GLFW");
    }

    window = glfwCreateWindow(800, 500, "Test App", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::exception("Could not create window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);

    renderer = new Renderer(*window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    bindCallbacks();

    Shader* shader = new Shader("VertexShader.glsl", "FragmentShader.glsl");
    
    int index = shaders.size();
    shaders[index] = shader;
    BASIC_SHADER_ID = index;
}

void Application::bindCallbacks()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {Application::getInstance()->key_callback(window, key, scancode, action, mods); });
    glfwSetErrorCallback([](int error, const char* description) -> void {Application::getInstance()->error_callback(error, description); });
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {Application::getInstance()->window_size_callback(window, width, height); });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void {Application::getInstance()->cursor_pos_callback(window, mouseXPos, mouseYPos); });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) -> void {Application::getInstance()->mouse_button_callback(window, button, action, mods); });
}

Application* Application::getInstance()
{
    if (instance == NULL)
    {
        instance = new Application();
    }
    return instance;
}

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();

    for (unsigned int i = 0; i < shaders.size(); i++)
    {
        delete shaders.at(i);
    }
    shaders.empty();

    for (int i = 0; i < scenes.size(); i++)
    {
        delete scenes.at(i);
    }

    scenes.clear();

    delete renderer;

    for (unsigned int i = 0; i < this->textures.size(); i++)
    {
        printf("Delete texture in unit %i\n", this->textures.at(i));
        glDeleteTextures(1, &this->textures.at(i));
    }
  
}

void Application::createScene(char* sceneName,  Camera * cam)
{
    Scene* newScene = new Scene(sceneName, cam);
    scenes.push_back(newScene);

    currentScene = newScene;
}

void Application::renderCurrentScene()
{
    renderer->renderScene(getCurrentScene());
}

Scene & Application::getCurrentScene()
{
    return *currentScene;
}

void Application::setCurrentScene(char * sceneName)
{
    bool found = false;
    for (int i = 0; i < scenes.size(); i++)
    {
        if (scenes.at(i)->getSceneName() == sceneName)
        {
            found = true;
            currentScene = scenes.at(i);
            break;
        }
    }
    if (!found)
    {
        printf("Scene with name: %s, was not found.\n", sceneName);
    }
}

void Application::error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    Direction direction = None;
    switch (key)
    {
    case GLFW_KEY_UP:
        direction = Forward;
        break;
    case GLFW_KEY_DOWN:
        direction = Backward;
        break;
    case GLFW_KEY_LEFT:
        direction = Left;
        break;
    case GLFW_KEY_RIGHT:
        direction = Right;
        break;
    case GLFW_KEY_SPACE:
        direction = Up;
        break;
    case GLFW_KEY_LEFT_CONTROL:
        direction = Down;
        break;
    }
    if (direction != None)
    {
        this->currentScene->getActiveCameraRef().moveCamera(direction);
    }

    if (mods == GLFW_MOD_CONTROL && key == GLFW_KEY_R)
    {
        this->currentScene->getActiveCameraRef().resetCamera();
    }

    if (key == GLFW_KEY_PAGE_DOWN)
    {
        
    }
    if (key == GLFW_KEY_PAGE_UP)
    {
        
    }

    this->currentScene->getActiveCameraRef().forceUpdate();


}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    //printf("cursor_pos_callback %d, %d \n", (int)mouseX, (int)mouseY);

    if (enableLookingAroud)
    {
        this->currentScene->getActiveCameraRef().mouseUpdate(glm::vec2(mouseX, mouseY));
    }
}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    //printf("mouse_button_callback %d, %d, %d \n", button, action, mods);
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        currentScene->swapCamera();
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            enableLookingAroud = true;
        }
        else if (action == GLFW_RELEASE)
        {
            enableLookingAroud = false;
            
            GLbyte color[4]; 
            GLfloat depth; 
            GLuint index;
            

            
            
            double cx, cy;
            glfwGetCursorPos(window, &cx, &cy);

            GLint x = (GLint)cx;
            GLint y = (GLint)cy;

            int w, h;
            glfwGetWindowSize(window, &w, &h);

            int newy = h - y;

            glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
            glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

            printf("Clicked on pixel %d, %d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index %u\n",
                        x, y, color[0], color[1], color[2], color[3], depth, index);

        }
    }
}

unsigned int Application::getNextId()
{
    return ++this->nextObjectId;
}

Shader const& Application::getBasicShader() const
{
    return *(shaders.at(BASIC_SHADER_ID));
}

Shader * Application::getShader(unsigned int shaderId)
{
    if (shaders.count(shaderId))
    {
        return (shaders.at(shaderId));
    }
    else
    {
        printf("Shader with id: %i, was not found! Will return basic shader.", shaderId);
        return (shaders.at(BASIC_SHADER_ID));
    }
}

Shader * Application::getShadowShader()
{
    if (shaders.count(SHADOW_SHADER_ID))
    {
        return (shaders.at(SHADOW_SHADER_ID));
    }
    else
    {
        throw new std::exception("Shadow shader is not set");
    }
}

unsigned int Application::getBasicShaderId() const
{
    return BASIC_SHADER_ID;
}

unsigned int Application::addShader(Shader * shader)
{
    unsigned int shaderId = this->shaders.size();
    shaders[shaderId] = shader;
    return shaderId;
}

unsigned int Application::addShadowShader(Shader * shader)
{
    unsigned int shaderId = this->shaders.size();
    shaders[shaderId] = shader;
    this->SHADOW_SHADER_ID = shaderId;
    return shaderId;
}

unsigned int Application::addTexture(const char * textureFile)
{
    //Texture with id 0 is reserved for shadow map.
    unsigned int textureId = 1 + this->textures.size();
    Texture tex;
    tex.loadTexture(textureFile, textureId);
    this->textures.push_back(textureId);

    return textureId;
}

unsigned int Application::addSkyBoxTexture(const char* x, const char* nx, const char* y, const char* ny, const char* z, const char* nz)
{
    unsigned int textureId = 1 + this->textures.size();
    Texture tex;
    tex.loadSkyBox(x, nx, y, ny, z, nz, textureId);
    this->textures.push_back(textureId);

    return textureId;
}
