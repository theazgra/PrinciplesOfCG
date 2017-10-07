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
    //currentScene = nullptr;

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

void Application::createScene(char* sceneName, Shader* shader)
{
    Scene* newScene = new Scene(sceneName, shader);
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
