// PrinciplesOfCG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include "models\sphere.h"
#include <vector>

#include "ObjectFactory.h"



int main()
{
    Application* app = Application::getInstance();                

    app->createScene("Basic scene", 
        new Camera(0, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

    app->getCurrentScene().addCamera(glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(0.0f, 0.0f, 2.0f));
    unsigned int houseTexture = app->addTexture("test.png");
    unsigned int mine = app->addTexture("mine.jpg");

    app->getCurrentScene().addDrawableObject(
        ObjectFactory::createAssimpObject(
            "test.obj",
            88,
            app->getBasicShaderId(),
            houseTexture));
        
    

    //app->getCurrentScene().addSphere().translate(glm::vec3(2.0f, 0.0f, 2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(2.0f, 0.0f, -2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(-2.0f, 0.0f, -2.0f));
    //app->getCurrentScene().addSphere().translate(glm::vec3(-2.0f, 0.0f, 2.0f));
    //app->getCurrentScene().addSphere().resize(glm::vec3(20.0f, 20.0f, 20.0f));
    //app->getCurrentScene().addSphere(new Shader("VertexShader.glsl", "FragmentShader2.glsl"));
    //app->getCurrentScene().addSphere(new Shader("VertexShader.glsl", "FragmentShader2.glsl")).translate(glm::vec3(2.0f, 0.0f, 2.0f));

    

    //PlainObject * plain = &app->getCurrentScene().addPlainObject();
    //plain->translate(glm::vec3(0.0f, -10.0f, 0.0f));
    //plain->resize(glm::vec3(10.0f, 10.0f, 10.0f));
    
    app->renderCurrentScene();

    delete app;

    return 0;
}



