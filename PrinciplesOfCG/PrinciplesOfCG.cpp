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
        new Shader("VertexShader.glsl", "FragmentShader.glsl", "tex.jpg"), 
        new Camera(0, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
        
    app->getCurrentScene().addCamera(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 2.0f));
    

    //app->getCurrentScene().addSphere().translate(glm::vec3(2.0f, 0.0f, 2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(2.0f, 0.0f, -2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(-2.0f, 0.0f, -2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(-2.0f, 0.0f, 2.0f));
    //app->getCurrentScene().addSphere().resize(glm::vec3(20.0f, 20.0f, 20.0f));
    app->getCurrentScene().addSphere();

    PlainObject * plain = &app->getCurrentScene().addPlainObject();
    //plain->rotate(90.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    plain->translate(glm::vec3(0.0f, -10.0f, 0.0f));
    plain->resize(glm::vec3(10.0f, 10.0f, 10.0f));
    
    app->renderCurrentScene();

    delete app;

    return 0;
}


