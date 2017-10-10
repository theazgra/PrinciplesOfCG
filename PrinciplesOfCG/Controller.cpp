#include "stdafx.h"
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

    if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            printf("up\n");
            
            break;
        case GLFW_KEY_DOWN:
            printf("down\n");
            break;
        case GLFW_KEY_LEFT:
            printf("left\n");
            break;
        case GLFW_KEY_RIGHT:
            printf("right\n");
            break;
        }
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
}