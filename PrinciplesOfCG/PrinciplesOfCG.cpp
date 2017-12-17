// PrinciplesOfCG.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Application.h"
#include "PrinciplesOfCG.h"

int main()
{
    Application* app = Application::getInstance();      
    
    app->setUpBasicScene();
    
    delete app;

    return 0;
}