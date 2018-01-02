#include "stdafx.h"
#include "Application.h"
#include "ObjectFactory.h"

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
    ++keyClickCount;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    Direction direction = None;
    switch (key)
    {
    case GLFW_KEY_TAB:
        if (keyClickCount > 2) 
        {
            this->moveCamera = !this->moveCamera;
            printf("Switched to %s moving mode.\n", moveCamera ? "camera" : "shadow producing light");
            keyClickCount = 0;
        }
        
        break;

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
        if (!moveCamera) {
            switch (direction)
            {
            case Up:
                currentScene->getShadowLight()->move(glm::vec3(0, 0.2, 0));
                break;
            case Down:
                currentScene->getShadowLight()->move(glm::vec3(0, -0.2, 0));
                break;
            case Left:
                currentScene->getShadowLight()->move(glm::vec3(-0.2, 0.0, 0));
                break;
            case Right:
                currentScene->getShadowLight()->move(glm::vec3(0.2, 0.0, 0));
                break;
            case Forward:
                currentScene->getShadowLight()->move(glm::vec3(0, 0.0, -0.2));
                break;
            case Backward:
                currentScene->getShadowLight()->move(glm::vec3(0, 0.2, 0.2));
                break;
            default:
                break;

            }
        }
        else
        {
            this->currentScene->getActiveCameraRef().moveCamera(direction);
        }
    }

    if (mods == GLFW_MOD_CONTROL && key == GLFW_KEY_R)
    {
        this->currentScene->getActiveCameraRef().resetCamera();
    }

    if (mods == GLFW_MOD_CONTROL && key == GLFW_KEY_S && keyClickCount >= 3) 
    {
        printf("Saving scene...\n");
        
        if (xmlScene.saveScene(*currentScene))
            printf("Scene saved.\n");
        else
            printf("Error occured when saving scene.");

        keyClickCount = 0;
    }

    this->currentScene->getActiveCameraRef().forceUpdate();
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    currentScene->getActiveCameraRef().setDimensions(width, height);
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {

    if (enableLookingAroud)
    {
        this->currentScene->getActiveCameraRef().mouseUpdate(glm::vec2(mouseX, mouseY));
    }
}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    
    double cx, cy;
    glfwGetCursorPos(window, &cx, &cy);

    GLint x = (GLint)cx;
    GLint y = (GLint)cy;

    int w, h;
    glfwGetWindowSize(window, &w, &h);

    int newy = h - y;
    GLbyte color[4];
    GLfloat depth;
    GLuint index;
    glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

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
            

            printf("Clicked on pixel %d, %d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index %u\n",
                        x, y, color[0], color[1], color[2], color[3], depth, index);
        }
        
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        currentScene->deleteObject(index);
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

unsigned int Application::addShader(Shader * shader, unsigned int shaderId)
{
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

unsigned int Application::addShadowShader(Shader * shader, unsigned int shaderId)
{
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

unsigned int Application::addTexture(const char * textureFile, unsigned int textureId)
{
    if (textureId == 0)
        throw new std::exception("Texture with id 0 is reserved for shadow texture.");
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

unsigned int Application::addSkyBoxTexture(const char * x, const char * nx, const char * y, const char * ny, const char * z, const char * nz, unsigned int textureId)
{
    if (textureId == 0)
        throw new std::exception("Texture with id 0 is reserved for shadow texture.");

    Texture tex;
    tex.loadSkyBox(x, nx, y, ny, z, nz, textureId);
    this->textures.push_back(textureId);

    return textureId;
}


void Application::loadScene(const char * xmlSceneFile)
{
    Scene * loadedScene = this->xmlScene.loadScene(xmlSceneFile);
    scenes.push_back(loadedScene);
    currentScene = loadedScene;
}


void Application::setUpBasicScene()
{
    XmlScene xmlScene;
    Scene * scene = xmlScene.loadScene("BasicScene.xml");

    scenes.push_back(scene);
    currentScene = scene;
    renderCurrentScene();
    return;


    //createScene()

    //Create scene
    createScene("Basic scene",
        new Camera(0, glm::vec3(10.0f, 12.0f, -4.0f), glm::vec3(0.0f, 4.0f, 0.0f)));

    
    currentScene->addCamera(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 2.0f));

    addShadowShader(new Shader("VSShadow.glsl", "FSShadow.glsl"));
    unsigned int skyBoxShader = addShader(new Shader("VSCubeMap.glsl", "FSCubeMap.glsl"));
    //unsigned int shadowTexShader = addShader(new Shader("VertexShader.glsl", "FragmentShader2.glsl"));
    unsigned int grassTexture = addTexture("tex.jpg");
    unsigned int houseTexture = addTexture("test.png");
    unsigned int redTexture = addTexture("mine.png");
    unsigned int cylinderTexture = addTexture("normal/diffuse.bmp");
    unsigned int houseNormal = addTexture("normal/houseNormal.png");
    unsigned int cylinderNormal = addTexture("normal/cylinder_normal.bmp");
    unsigned int skyBoxTexture = addSkyBoxTexture(
        "sky/cubemap/posx.jpg",
        "sky/cubemap/negx.jpg",
        "sky/cubemap/posy.jpg",
        "sky/cubemap/negy.jpg",
        "sky/cubemap/posz.jpg",
        "sky/cubemap/negz.jpg"
    );

    PlainObject * plain = ObjectFactory::createPlain(
        getNextId(),
        getBasicShaderId(),
        grassTexture);

    plain->resize(glm::vec3(50.0f));
    currentScene->addDrawableObject(plain);

    //PlainObject * shadowMap = ObjectFactory::createPlain(
    //    getNextId(),
    //    shadowTexShader,
    //    0);

    //shadowMap->resize(glm::vec3(5.0f));
    //shadowMap->translate(glm::vec3(3.0f, 1.0f, 0.0f));
    //shadowMap->rotate(glm::degrees(45.0f), glm::vec3(1, 0, 0));
    //currentScene->addDrawableObject(shadowMap);

    DrawableObject * house = ObjectFactory::createAssimpObject("test.obj",getNextId(),getBasicShaderId(),houseTexture);
    
    house->setNormalTextureId(houseNormal);    
    currentScene->addDrawableObject(house);


    DrawableObject * cylinder = ObjectFactory::createAssimpObject(
        "normal/cylinder.obj",
        getNextId(),
        getBasicShaderId(),
        cylinderTexture);

    cylinder->resize(glm::vec3(1, 2, 1));
    cylinder->translate(glm::vec3(-15.0f, 0.0f, 0.0f));
    cylinder->setNormalTextureId(cylinderNormal);
    currentScene->addDrawableObject(cylinder);

    currentScene->addSkyBox(
        ObjectFactory::createAssimpObject(
            "sky/skybox.obj",
            getNextId(),
            skyBoxShader,
            skyBoxTexture
        )
    );

    SpotLight * spot = ObjectFactory::createSpotLight(
        getNextId(),
        glm::vec3(5.0f, 5.0f, 5.0f) * 2.0f,
        glm::radians(12.5f),
        glm::radians(20.0f),
        glm::vec3(00, 1, 0.02)
        //glm::vec3(-37, -9, 0.02)
        //glm::vec3(-15.0f, -0.5f, 0.0f)
    );
    spot->setPosition(glm::vec3(0.0f, 18.0f, 0.0f));
    //spot->setPosition(glm::vec3(-27.0f, 12.0f, 0.04f));
    currentScene->addShadowLight(spot);
    currentScene->addCamera(spot->getWorldPosition(), spot->getLightInfo().direction);
    
    currentScene->addCamera(glm::vec3(15.0f, 18.0f, 0.0f), glm::vec3(0.5f, 1.0f, 0.1f));


    //currentScene->addShadowLight(ObjectFactory::createDirectionalLight(
    //    getNextId(),
    //    glm::vec3(1.5f, 1.5f, 1.5f), //glm::vec3(5.0f, 5.0f, 5.0f)
    //    glm::vec3(20.0f, 5.0f, 0.0f)
    //));

    DrawableObject* d = ObjectFactory::createSphere(getNextId(), getBasicShaderId(), redTexture);
    d->translate(glm::vec3(5.0f, 6.5f, 0.0f));

    DrawableObject* d2 = ObjectFactory::createSphere(getNextId(), getBasicShaderId(), redTexture);
    d2->translate(glm::vec3(0.0f, 8.5f, -5.0f));

    DrawableObject* d3 = ObjectFactory::createSphere(getNextId(), getBasicShaderId(), redTexture);
    d3->translate(glm::vec3(5.0f, 8.5f, 5.0f));

    currentScene->addDrawableObject(d);
    currentScene->addDrawableObject(d2);
    currentScene->addDrawableObject(d3);

    renderCurrentScene();
}
