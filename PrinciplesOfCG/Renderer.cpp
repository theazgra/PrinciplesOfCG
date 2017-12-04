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


void Renderer::renderDrawableObjects(Scene& scene)
{
    int ignore = -1;
    for (unsigned int i = 0; i < scene.getDrawableObjects().size(); i++)
    {
        if (scene.getDrawableObjects().at(i)->isSkyBox())
        {
            ignore = i;

            unsigned int objectShaderId = scene.getDrawableObjects().at(i)->getShaderId();


            if (objectShaderId != lastShaderId)
            {
                Application::getInstance()->getShader(objectShaderId)->useProgram();
            }

            Application::getInstance()->getShader(objectShaderId)->applyTexture(
                scene.getDrawableObjects().at(i)->getTextureId());

            Application::getInstance()->getShader(objectShaderId)->applyCamera();
            Application::getInstance()->getShader(objectShaderId)->applyLight();

            Application::getInstance()->getShader(objectShaderId)->modelTransform(*(scene.getDrawableObjects().at(i)));

            this->lastShaderId = objectShaderId;

            glBindVertexArray(scene.getDrawableObjects().at(i)->getVAO());


            glStencilFunc(GL_ALWAYS, scene.getDrawableObjects().at(i)->getObjectId(), 0xFF);

            if (scene.getDrawableObjects().at(i)->hasIndices())
            {
                glDrawElements(
                    GL_TRIANGLES,
                    scene.getDrawableObjects().at(i)->getIndicesCount(),
                    GL_UNSIGNED_INT,
                    nullptr);
            }
            else
            {
                glDrawArrays(
                    GL_TRIANGLES,
                    0,
                    scene.getDrawableObjects().at(i)->getVerticesCount());
            }

            glClear(GL_DEPTH_BUFFER_BIT);
            break;
        }
    }
    
    
    for (unsigned int i = 0; i < scene.getDrawableObjects().size(); i++)
    {
        if (ignore == i)
            continue;


        unsigned int objectShaderId = scene.getDrawableObjects().at(i)->getShaderId();
        
        
        if (objectShaderId != lastShaderId)
        {
            Application::getInstance()->getShader(objectShaderId)->useProgram();
        }

        Application::getInstance()->getShader(objectShaderId)->applyTexture(
            scene.getDrawableObjects().at(i)->getTextureId());

        Application::getInstance()->getShader(objectShaderId)->applyCamera();
        Application::getInstance()->getShader(objectShaderId)->applyLight();

        Application::getInstance()->getShader(objectShaderId)->modelTransform(*(scene.getDrawableObjects().at(i)));
        
        this->lastShaderId = objectShaderId;

        glBindVertexArray(scene.getDrawableObjects().at(i)->getVAO());
        
        
        glStencilFunc(GL_ALWAYS, scene.getDrawableObjects().at(i)->getObjectId(), 0xFF);

        if (scene.getDrawableObjects().at(i)->hasIndices())
        {
            glDrawElements(
                GL_TRIANGLES,
                scene.getDrawableObjects().at(i)->getIndicesCount(),
                GL_UNSIGNED_INT,
                nullptr);
        }
        else 
        {
            glDrawArrays(
                GL_TRIANGLES, 
                0, 
                scene.getDrawableObjects().at(i)->getVerticesCount());
        }

        //if (scene.getDrawableObjects().at(i)->isSkyBox())
        //{
        //    glClear(GL_DEPTH_BUFFER_BIT);
        //}

    }
}