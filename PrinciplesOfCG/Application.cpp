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

    if (mods != GLFW_MOD_SHIFT)
    {
        Direction d = None;
        switch (key)
        {
        case GLFW_KEY_UP:
            d = Forward;
            break;
        case GLFW_KEY_DOWN:
            d = Backward;
            break;
        case GLFW_KEY_LEFT:
            d = Left;
            break;
        case GLFW_KEY_RIGHT:
            d = Right;
            break;
        case GLFW_KEY_SPACE:
            d = Up;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            d = Down;
            break;
        }
        if (d != None)
        {
            this->currentScene->getActiveCameraRef().moveCamera(d);
        }

        if (mods == GLFW_MOD_CONTROL && key == GLFW_KEY_R)
        {
            this->currentScene->getActiveCameraRef().resetCamera();
        }

        if (key == GLFW_KEY_PAGE_DOWN)
        {
            this->currentScene->getPointLight().setPower(this->currentScene->getPointLight().getPower() + 2.0f);
        }
        if (key == GLFW_KEY_PAGE_UP)
        {
            this->currentScene->getPointLight().setPower(this->currentScene->getPointLight().getPower() - 2.0f);
        }
    }
    else if (mods == GLFW_MOD_SHIFT)
    {
        Direction d = None;
        switch (key)
        {
        case GLFW_KEY_UP:
            d = Forward;
            break;
        case GLFW_KEY_DOWN:
            d = Backward;
            break;
        case GLFW_KEY_LEFT:
            d = Left;
            break;
        case GLFW_KEY_RIGHT:
            d = Right;
            break;
        case GLFW_KEY_SPACE:
            d = Up;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            d = Down;
            break;
        }
        if (d != None)
        {
            this->currentScene->getActiveCameraRef().moveCameraAndEye(d);
        }
    }



}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    //printf("cursor_pos_callback %d, %d \n", (int)mouseX, (int)mouseY);

    if (enableLookingAroud)
    {
        mouseChange++;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //mouseX = (mouseX > width / 2) ? (mouseX - width / 2) * -1 : (width / 2 - mouseX) ;
        mouseY = (mouseY > height / 2) ? (height / 2 - mouseY)  * -1 : (mouseY - height / 2);

        //printf("mouse: [x: %f; y: %f]\n", mouseX, mouseY);

        int deltaX = lastXPosition - mouseX;
        int deltaY = lastYPosition - mouseY;
        printf("delta: [x: %i; y: %i]\n", deltaX, deltaY);

        //int deltaX = lastXPosition - mouseX;
        //int deltaY = lastYPosition - mouseY;

        lastXPosition = mouseX;
        lastYPosition = mouseY;

        //return;
        if (mouseChange > 2)
        {
            mouseChange = 0;
            this->currentScene->getActiveCameraRef().lookAround(deltaX, deltaY);
        }
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
            enableLookingAroud = true;
        else if (action == GLFW_RELEASE)
        {
            enableLookingAroud = false;


            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            lastXPosition = width / 2;
            lastYPosition = height / 2;
        }
    }
}
