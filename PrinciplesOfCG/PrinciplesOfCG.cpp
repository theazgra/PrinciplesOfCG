// PrinciplesOfCG.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Application.h"
#include "PrinciplesOfCG.h"
#include "BezierCurve.h"

int main()
{
    Application* app = Application::getInstance();      
    app->loadScene("BasicScene.xml");
    app->renderCurrentScene();
    delete app;

    //BezierCurve bezier(
    //    glm::vec3(0.0, 0.0, 0.0),
    //    glm::vec3(1.0, 2.0, 0.0),
    //    glm::vec3(4.0, 2.0, 0.0),
    //    glm::vec3(5.0, 0.0, 0.0)
    //);

    //while (bezier)
    //{
    //    glm::vec3 point = bezier.getPointOnCurve();
    //    printf("[%.3f; %.3f; %.3f]\n", point.x, point.y, point.z);
    //}


    
    

    return 0;
}