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

void Renderer::renderScene(Scene const& scene)
{
    lastRenderTime = glfwGetTime();
    frameCount = 0;

    scene.getDrawableObjects().at(1)->translate(glm::vec3(-0.5f, 0.0f, 0.0f));
    scene.getDrawableObjects().at(2)->translate(glm::vec3(-0.5f, -0.5f, 0.0f));
    scene.getDrawableObjects().at(3)->translate(glm::vec3(0.0f, -0.5f, 0.0f));

    while (!glfwWindowShouldClose(this->window))
    {
        reportRenderTime();
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

void Renderer::renderDrawableObjects(Scene const& scene)
{
    for (int i = 0; i < scene.getDrawableObjects().size(); i++)
    {
        scene.getDrawableObjects().at(i)->rotate(0.05f, glm::vec3(1.0f, 1.0f, 0.0f));

        if (scene.getDrawableObjects().at(i)->hasOwnShader())
        {
            scene.getDrawableObjects().at(i)->getShader().useProgram();
            scene.getDrawableObjects().at(i)->getShader().modelTransform(*(scene.getDrawableObjects().at(i)));
        }
        else
        {
            scene.getBasicShader().useProgram();
            scene.getBasicShader().modelTransform(*(scene.getDrawableObjects().at(i)));
        }

        glBindVertexArray(scene.getDrawableObjects().at(i)->getVAO());

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