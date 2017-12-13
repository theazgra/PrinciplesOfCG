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

    app->getCurrentScene().addCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 2.0f));
    app->addShadowShader(new Shader("VSShadow.glsl", "FSShadow.glsl"));
    unsigned int skyBoxShader = app->addShader(new Shader("VSCubeMap.glsl", "FSCubeMap.glsl"));
    unsigned int shadowTexShader = app->addShader(new Shader("VertexShader.glsl", "FragmentShader2.glsl"));
    unsigned int grassTexture = app->addTexture("tex.jpg");
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

    PlainObject * plain = ObjectFactory::createPlain(
        app->getNextId(),
        app->getBasicShaderId(),
        grassTexture);

    plain->resize(glm::vec3(50.0f));
    app->getCurrentScene().addDrawableObject(plain);

    PlainObject * shadowMap = ObjectFactory::createPlain(
        app->getNextId(),
        shadowTexShader,
        redTexture);

    shadowMap->resize(glm::vec3(5.0f));
    shadowMap->translate(glm::vec3(3.0f, 1.0f, 0.0f));
    shadowMap->rotate(glm::degrees(45.0f), glm::vec3(1, 0, 0));
    app->getCurrentScene().addDrawableObject(shadowMap);

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

    SpotLight * spot = ObjectFactory::createSpotLight(
        app->getNextId(),
        glm::vec3(5.0f, 5.0f, 5.0f),
        glm::radians(12.5f),
        glm::radians(20.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    spot->setPosition(glm::vec3(0.0f, 12.0f, 0.0f));
    
    app->getCurrentScene().addShadowLight(spot);
    
    
    //app->getCurrentScene().addShadowLight(ObjectFactory::createDirectionalLight(
    //    app->getNextId(),
    //    glm::vec3(5.0f, 5.0f, 5.0f),
    //    glm::vec3(0.0f, 1.0f, 0.0f)
    //));

    DrawableObject* d = ObjectFactory::createSphere(app->getNextId(), app->getBasicShaderId(), redTexture);
    d->translate(glm::vec3(0.0f, 9.0f, 0.0f));

    DrawableObject* d2 = ObjectFactory::createSphere(app->getNextId(), app->getBasicShaderId(), redTexture);
    d2->translate(glm::vec3(0.0f, 9.0f, -5.0f));

    DrawableObject* d3 = ObjectFactory::createSphere(app->getNextId(), app->getBasicShaderId(), redTexture);
    d3->translate(glm::vec3(0.0f, 9.0f, 5.0f));

    app->getCurrentScene().addDrawableObject(d);
    app->getCurrentScene().addDrawableObject(d2);
    app->getCurrentScene().addDrawableObject(d3);

    app->renderCurrentScene();

    delete app;

    return 0;
}



