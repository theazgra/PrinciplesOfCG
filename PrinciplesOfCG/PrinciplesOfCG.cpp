// PrinciplesOfCG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include "models\sphere.h"
#include <vector>

#include "ObjectFactory.h"



int main()
{   
    //std::vector<float> vertices = {
    //    0.0f, 0.0f, 0.0f,
    //    0.5f, 0.0f, 0.0f,
    //    0.5f, 0.5f, 0.0f,
    //    0.0f, 0.5f, 0.0f
    //};

    Application* app = Application::getInstance();                

    app->createScene("Basic scene", 
        new Shader("VertexShader.glsl", "FragmentShader2.glsl", "tex.jpg"), 
        new Camera(0, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
        
    app->getCurrentScene().addCamera(glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(0.0f, 0.0f, 2.0f));
    

    //app->getCurrentScene().addSphere().translate(glm::vec3(2.0f, 0.0f, 2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(2.0f, 0.0f, -2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(-2.0f, 0.0f, -2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(-2.0f, 0.0f, 2.0f));
    //app->getCurrentScene().addSphere().resize(glm::vec3(20.0f, 20.0f, 20.0f));
    //app->getCurrentScene().addSphere(new Shader("VertexShader.glsl", "FragmentShader2.glsl"));
    //app->getCurrentScene().addSphere(new Shader("VertexShader.glsl", "FragmentShader2.glsl")).translate(glm::vec3(2.0f, 0.0f, 2.0f));

    app->getCurrentScene().addDrawableObject(
        ObjectFactory::createAssimpObject(
            "drawer.obj", 
            88,
            app->getCurrentScene().getBasicShaderId(),
            1));

    //PlainObject * plain = &app->getCurrentScene().addPlainObject();
    //plain->translate(glm::vec3(0.0f, -10.0f, 0.0f));
    //plain->resize(glm::vec3(10.0f, 10.0f, 10.0f));
    
    app->renderCurrentScene();

    delete app;

    return 0;
}


