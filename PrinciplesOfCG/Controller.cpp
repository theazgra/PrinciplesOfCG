#include "stdafx.h"
#include "Application.h"
#include "Controller.h"


static double lastXPosition;
static double lastYPosition;
static bool enableLookingAroud = false;
static int mouseChange = 0;

static bool firstTime = true;

Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::init(int width, int height)
{
    lastXPosition = 0;
    lastYPosition = 0;
}

void Controller::error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
            Application::getInstance()->moveCamera(d);
        }

        if (mods == GLFW_MOD_CONTROL && key == GLFW_KEY_R)
        {
            Application::getInstance()->resetCamera();
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
            Application::getInstance()->moveCameraAndEye(d);
        }
    }



}

void Controller::window_size_callback(GLFWwindow* window, int width, int height) {
    //printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void Controller::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
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
            Application::getInstance()->lookAround(deltaX, deltaY);
        }
    }
}

void Controller::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    //printf("mouse_button_callback %d, %d, %d \n", button, action, mods);
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        Application::getInstance()->swapCamera();
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