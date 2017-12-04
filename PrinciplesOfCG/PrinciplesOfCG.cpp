// PrinciplesOfCG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include "models\sphere.h"
#include <vector>

#include "ObjectFactory.h"
#include "PrinciplesOfCG.h"



int main()
{
    Application* app = Application::getInstance();                

    app->createScene("Basic scene", 
        new Camera(0, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

    //app->getCurrentScene().addCamera(glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(0.0f, 0.0f, 2.0f));
    app->getCurrentScene().addCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 2.0f));
    unsigned int skyBoxShader = app->addShader(new Shader("VSCubeMap.glsl", "FSCubeMap.glsl"));
    unsigned int houseTexture = app->addTexture("test.png");
    unsigned int redTexture = app->addTexture("mine.jpg");
    unsigned int skyBoxTexture = app->addSkyBoxTexture(
        "sky/cubemap/posx.jpg",
        "sky/cubemap/negx.jpg",
        "sky/cubemap/posy.jpg",
        "sky/cubemap/negy.jpg",
        "sky/cubemap/posz.jpg",
        "sky/cubemap/negz.jpg"
    );

    app->getCurrentScene().addDrawableObject(
        ObjectFactory::createAssimpObject(
            "test.obj",
            app->getNextId(),
            app->getBasicShaderId(),
            houseTexture));

    app->getCurrentScene().addSkyBox(
        ObjectFactory::createAssimpObject(
            "sky/skybox.obj",
            app->getNextId(),
            skyBoxShader,
            skyBoxTexture
        )
    );

    app->getCurrentScene().addLight(
        ObjectFactory::createDirectionalLight(
            app->getNextId(),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(0.5f, 0.0f, 0.5f)
        )
    );

    //PointLight * pl = ObjectFactory::createPointLight(
    //    app->getNextId(),
    //    glm::vec3(1.0f, 1.0f, 1.0f)
    //);

    //pl->setPosition(glm::vec3(5.0f, 0.0f, 10.0f));

    //PointLight * pl2 = ObjectFactory::createPointLight(
    //    app->getNextId(),
    //    glm::vec3(3.0f, 1.0f, 1.0f)
    //);

    //pl2->setPosition(glm::vec3(-6.0f, 0.0f, -8.0f));

    //app->getCurrentScene().addLight(
    //  pl  
    //);

    //app->getCurrentScene().addLight(
    //    pl2
    //);
    //radians, 12.5, 17.5
    SpotLight * sl = ObjectFactory::createSpotLight(
        app->getNextId(),
        glm::vec3(3.0f, 3.0f, 3.0f),
        glm::radians(5.0f),
        glm::radians(6.5f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    sl->setPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    app->getCurrentScene().addLight(sl);

    
        
    

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



