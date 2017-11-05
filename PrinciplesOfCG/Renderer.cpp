#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(GLFWwindow& window, RenderType type)
{
    this->window = &window;
    this->renderType = type;
}


Renderer::~Renderer()
{
}

void Renderer::reportRenderTime() 
{
    frameCount++;
    double currentTime = glfwGetTime();
    if (currentTime - lastRenderTime >= 1.0)
    {
        printf("%f ms/frame\n", 1000.0 / double(frameCount));
        frameCount = 0;
        lastRenderTime += 1;
    }
}

void Renderer::renderScene(Scene & scene)
{
    lastRenderTime = glfwGetTime();
    frameCount = 0;

    while (!glfwWindowShouldClose(this->window))
    {
#if REPORT_FRAME_TIME   
        reportRenderTime();
#endif
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderDrawableObjects(scene);

        glfwPollEvents();

        glfwSwapBuffers(this->window);
    }
}

void Renderer::setRenderType(RenderType renderType)
{
    this->renderType = renderType;
}

void Renderer::renderDrawableObjects(Scene& scene)
{
    //scene.getPointLight().move(glm::vec3(0.0f, 0.01f, 0.01f));
    
    for (unsigned int i = 0; i < scene.getDrawableObjects().size(); i++)
    {
        unsigned int objectShaderId = scene.getDrawableObjects().at(i)->getShaderId();
        
        
        if (objectShaderId != lastShaderId)
        {
            scene.getShader(objectShaderId).useProgram();
        }
        scene.getShader(objectShaderId).applyCamera();
        scene.getShader(objectShaderId).applyLight();

        scene.getShader(objectShaderId).modelTransform(*(scene.getDrawableObjects().at(i)));
        
        this->lastShaderId = objectShaderId;

        glBindVertexArray(scene.getDrawableObjects().at(i)->getVAO());
        
        glStencilFunc(GL_ALWAYS, scene.getDrawableObjects().at(i)->getObjectId(), 0xFF);

        switch (renderType)
        {
            case Quads:
            {
                glDrawArrays(GL_QUADS, 0, scene.getDrawableObjects().at(i)->getVerticesCount());
                break;
            }
                
            case Triangles:
            {
                glDrawArrays(GL_TRIANGLES, 0, scene.getDrawableObjects().at(i)->getVerticesCount());
                break;
            }
        }
        
        
    }
}