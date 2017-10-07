// Cviceni2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Application.h"

float points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

/*
0.0f, 0.5f, 0.0f,
0.5f, -0.5f, 0.0f,
-0.5f, -0.5f, 0.0f
/*/
int main()
{
    //rectangle
    std::vector<float> vertices = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    //triangle
   /* std::vector<float> vertices = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.25f, 0.5f, 0.0f
    };*/

    Application* app = Application::getInstance();
    app->setRenderType(Quads);

    app->createScene("Basic scene", new Shader("VertexShader.glsl", "FragmentShader.glsl"));
    app->getCurrentScene().addObject(vertices);
    app->getCurrentScene().addObject(vertices);
    app->getCurrentScene().addObject(vertices);
    app->getCurrentScene().addObject(vertices);
    

    app->renderCurrentScene();

    delete app;

    return 0;

    return 0;
}


