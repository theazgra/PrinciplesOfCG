#pragma once
#include "GLFW\glfw3.h"
class Controller
{
public:
    Controller();
    ~Controller();

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void error_callback(int error, const char* description);
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

