#include "stdafx.h"
#include "Application.h"

static Application* instance;

GLFWwindow & Application::getWindow()
{
    return *window;
}

void Application::setRenderType(RenderType renderType)
{
    renderer->setRenderType(renderType);
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

    scenes = new std::vector<Scene*>();

    renderer = new Renderer(*window, Triangles);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    bindCallbacks();
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

    for (int i = 0; i < scenes->size(); i++)
    {
        delete scenes->at(i);
    }

    scenes->clear();
    delete scenes;

    delete renderer;
}

void Application::createScene(char* sceneName, Shader* shader, Camera * cam)
{
    Scene* newScene = new Scene(sceneName, shader, cam);
    scenes->push_back(newScene);

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
    for (int i = 0; i < scenes->size(); i++)
    {
        if (scenes->at(i)->getSceneName() == sceneName)
        {
            found = true;
            currentScene = scenes->at(i);
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
        this->currentScene->getPointLight().setPower(this->currentScene->getPointLight().getPower() + 0.1f);
    }
    if (key == GLFW_KEY_PAGE_UP)
    {
        this->currentScene->getPointLight().setPower(this->currentScene->getPointLight().getPower() - 0.1f);
    }

    this->currentScene->getActiveCameraRef().forceUpdate();
    this->currentScene->getPointLight().forceUpdate();


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
            //int newy = (int)camera->getResolution().y - y - 10;
            
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            int sX, sY;
            glfwGetWindowSize(window, &sX, &sY);
            int newy = sY - y - 10;
            glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
            glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
            printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n\n", x, y, color[0], color[1], color[2], color[3],
                depth, index);
            
            //glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            //glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        }
    }
}
