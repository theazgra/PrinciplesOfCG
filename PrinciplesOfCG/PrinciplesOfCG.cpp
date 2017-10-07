// PrinciplesOfCG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include <vector>


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
}

