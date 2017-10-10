#include "stdafx.h"
#include "Application.h"
#include "Controller.h"




Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }



    Direction d = None;
    switch (key)
    {
    case GLFW_KEY_UP:
        d = Forward;
        printf("up\n");
        break;
    case GLFW_KEY_DOWN:
        d = Backward;
        printf("down\n");
        break;
    case GLFW_KEY_LEFT:
        d = Left;
        printf("left\n");
        break;
    case GLFW_KEY_RIGHT:
        d = Right;
        printf("right\n");
        break;
    case GLFW_KEY_SPACE:
        d = Up;
        printf("space\n");
        break;
    case GLFW_KEY_LEFT_SHIFT:
        d = Down;
        printf("l shift\n");
        break;
    }
    if (d != None)
    {
        Application::getInstance()->moveCamera(d);
    }
    

}

void Controller::window_size_callback(GLFWwindow* window, int width, int height) {
    //printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void Controller::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    //printf("cursor_pos_callback %d, %d \n", (int)mouseX, (int)mouseY);
}

void Controller::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    //printf("mouse_button_callback %d, %d, %d \n", button, action, mods);
    if (action == GLFW_RELEASE)
    {
        Application::getInstance()->swapCamera();
    }
}