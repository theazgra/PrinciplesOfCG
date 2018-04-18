// PrinciplesOfCG.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Application.h"
#include "PrinciplesOfCG.h"
#include "BezierCurve.h"

int main()
{
    Application* app = Application::getInstance();      
    app->loadScene("BasicScene.xml");
    app->getCurrentScene().spawnZombies(10);
    app->renderCurrentScene();
    delete app;

    return 0;
}