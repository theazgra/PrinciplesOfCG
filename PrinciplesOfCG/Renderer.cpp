#include "stdafx.h"
#include "Renderer.h"
#include "Application.h"

Renderer::Renderer(GLFWwindow& window)
{
    this->window = &window;

    GLint shadowTextureWidth = 1024;
    GLint shadowTextureHeight = 1024;
    this->shadowFrameBuffer = 0;

    glGenFramebuffers(1, &this->shadowFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->shadowFrameBuffer);


    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, shadowTextureWidth, shadowTextureHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
    glDrawBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw new std::exception("Error in depth texture");

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

void Renderer::shadowPass(Scene & scene)
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->shadowFrameBuffer);
    LightStruct shadowProducingLight = scene.getShadowLight().getLightInfo();

    if (shadowProducingLight.lightType == SPOT_LIGHT)
    {
        /*
        this->target = glm::vec3(
        target.x - worldPosition.x,
        target.y - worldPosition.y,
        target.z - worldPosition.z
        );
        */

        glm::vec3 tar = glm::vec3(
            0 - shadowProducingLight.position.x,
            1 - shadowProducingLight.position.y,
            0 - shadowProducingLight.position.z
            );

        this->depthProjectionMatrix = glm::perspective<float>(glm::radians(45.0f), 1.0f, 2.0f, 50.0f);
        //this->depthViewMatrix = glm::lookAt(
        //    shadowProducingLight.position,
        //    shadowProducingLight.position - shadowProducingLight.direction,
        //    glm::vec3(0, 1, 0));

        this->depthViewMatrix = glm::lookAt(
            glm::vec3(0, 15, 0),
            glm::vec3(0, 15, 0) + tar,
            glm::vec3(0, 1, 0));
    }
    else
    {
        this->depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
        this->depthViewMatrix = glm::lookAt(scene.getShadowLight().getLightInfo().direction, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    }




    Application::getInstance()->getShadowShader()->setCameraMatrices(
        this->depthViewMatrix,
        this->depthProjectionMatrix,
        glm::vec3());

    Application::getInstance()->getShadowShader()->useProgram();

    for (unsigned int i = 0; i < scene.getDrawableObjects().size(); i++)
    {
        if (!scene.getDrawableObjects().at(i)->isSkyBox())
        {
            Application::getInstance()->getShadowShader()->modelTransform(*(scene.getDrawableObjects().at(i)));
            glBindVertexArray(scene.getDrawableObjects().at(i)->getVAO());

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
        }
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->depthTexture);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

        shadowPass(scene);
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

    Application::getInstance()->getShader(objectShaderId)->setDepthMatrices(
        this->depthViewMatrix,
        this->depthProjectionMatrix
    );

    Application::getInstance()->getShader(objectShaderId)->applyTexture(
        obj.getTextureId());

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