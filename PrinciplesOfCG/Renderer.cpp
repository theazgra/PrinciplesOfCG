#include "stdafx.h"
#include "Renderer.h"
#include "Application.h"

Renderer::Renderer(GLFWwindow& window)
{
    this->window = &window;
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


void Renderer::renderObject(DrawableObject & obj)
{
    unsigned int objectShaderId = obj.getShaderId();


    if (objectShaderId != lastShaderId)
    {
        Application::getInstance()->getShader(objectShaderId)->useProgram();
    }

    Application::getInstance()->getShader(objectShaderId)->applyTexture(
        obj.getTextureId());

    Application::getInstance()->getShader(objectShaderId)->applyCamera();
    Application::getInstance()->getShader(objectShaderId)->applyLight();

    Application::getInstance()->getShader(objectShaderId)->modelTransform(obj);

    this->lastShaderId = objectShaderId;

    glBindVertexArray(obj.getVAO());


    glStencilFunc(GL_ALWAYS, obj.getObjectId(), 0xFF);

    if (obj.hasIndices())
    {
        glDrawElements(
            GL_TRIANGLES,
            obj.getIndicesCount(),
            GL_UNSIGNED_INT,
            nullptr);
    }
    else
    {
        glDrawArrays(
            GL_TRIANGLES,
            0,
            obj.getVerticesCount());
    }
}

void Renderer::renderDrawableObjects(Scene& scene)
{
    int ignore = -1;
    for (unsigned int i = 0; i < scene.getDrawableObjects().size(); i++)
    {
        if (scene.getDrawableObjects().at(i)->isSkyBox())
        {
            ignore = i;
            renderObject(*scene.getDrawableObjects().at(i));

            glClear(GL_DEPTH_BUFFER_BIT);
            break;
        }
    }
    
    
    for (unsigned int i = 0; i < scene.getDrawableObjects().size(); i++)
    {
        if (ignore == i)
            continue;

        renderObject(*scene.getDrawableObjects().at(i));
    }
}