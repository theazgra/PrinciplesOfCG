// PrinciplesOfCG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include "models\sphere.h"
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

    Application* app = Application::getInstance();
    
    app->setRenderType(Triangles);                                        

    app->createScene("Basic scene", 
        new Shader("VertexShader.glsl", "FragmentShader.glsl"), 
        new Camera(0, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
        //new Camera(0, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(-10.0f, -0.0f, 0.0f)));
    
    //app->getCurrentScene().addCamera(glm::vec3(-7.0f, 5.0f, 8.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    app->getCurrentScene().addCamera(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 2.0f));
    //app->getCurrentScene().addCamera(glm::vec3(5.0f,5.0f,5.0f), glm::vec3(-5.0f, -5.0f, -5.0f));

    app->getCurrentScene().addSphere().translate(glm::vec3(2.0f, 0.0f, 2.0f));
    app->getCurrentScene().addSphere().translate(glm::vec3(2.0f, 0.0f, -2.0f));
    app->getCurrentScene().addSphere().translate(glm::vec3(-2.0f, 0.0f, -2.0f));
    app->getCurrentScene().addSphere().translate(glm::vec3(-2.0f, 0.0f, 2.0f));

    app->renderCurrentScene();

    delete app;

    return 0;
}

