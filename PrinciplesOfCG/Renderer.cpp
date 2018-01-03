#include "stdafx.h"
#include "Renderer.h"
#include "Application.h"

Renderer::Renderer(GLFWwindow& window)
{
    this->window = &window;

    int width, height;
    glfwGetWindowSize(&window, &width, &height);

    GLint shadowTextureWidth = width;// 1024;
    GLint shadowTextureHeight = height;// 1024;
    this->shadowFrameBuffer = 0;

    this->offsetMatrix = glm::mat4(
        glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
        glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
    );


    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, shadowTextureWidth, shadowTextureHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);


    glGenFramebuffers(1, &this->shadowFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->shadowFrameBuffer);
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
    glClear(GL_DEPTH_BUFFER_BIT);

    LightStruct shadowProducingLight = scene.getShadowLight()->getLightInfo();
    glm::mat4 depthModelMatrix = glm::mat4(1.0);
    glm::mat4 depthProjectionMatrix;
    glm::mat4 depthViewMatrix;

    if (shadowProducingLight.lightType == SPOT_LIGHT)
    {
        Camera lightCam(0, shadowProducingLight.position, shadowProducingLight.direction);
        depthViewMatrix = lightCam.getViewMatrix();
        depthProjectionMatrix = lightCam.getProjectionMatrix();
        //glm::vec3 lightInvDir = glm::vec3(0.0f, -2, 0);
        //depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
        //depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }
    else
    {
        depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
        Camera lightCam(0, shadowProducingLight.position, shadowProducingLight.direction);
        depthViewMatrix = lightCam.getViewMatrix();
        //printf("pos: x: %f y: %f z: %f \n", shadowProducingLight.position.x, shadowProducingLight.position.y, shadowProducingLight.position.z);
        //printf("target: x: %f y: %f z: %f \n", shadowProducingLight.target.x, shadowProducingLight.target.y, shadowProducingLight.target.z);
    }

    //depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
    depthVP = depthProjectionMatrix * depthViewMatrix;

    

    DrawableObject tmp(0);
    
    Application::getInstance()->getShadowShader()->useProgram();
    for (unsigned int i = 0; i < scene.getDrawableObjects().size(); i++)
    {
        if (!scene.getDrawableObjects().at(i)->isSkyBox())
        {
            Application::getInstance()->getShadowShader()->applyCamera();
            //Application::getInstance()->getShadowShader()->setDepthMVP(depthMVP);
            Application::getInstance()->getShadowShader()->setDepthVP(depthVP);
            Application::getInstance()->getShadowShader()->modelTransform(*(scene.getDrawableObjects().at(i)));

            //Application::getInstance()->getShadowShader()->modelTransform(tmp);
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

        //Shadows are not working atm.
        shadowPass(scene);
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

    //glm::mat4 DepthBiasMVP = this->offsetMatrix * depthMVP;
    glm::mat4 DepthBiasMVP = this->offsetMatrix * depthVP;

    Application::getInstance()->getShader(objectShaderId)->applyCamera();
    Application::getInstance()->getShader(objectShaderId)->applyLight();
    //Application::getInstance()->getShader(objectShaderId)->setDepthBiasMVP(DepthBiasMVP);
    Application::getInstance()->getShader(objectShaderId)->setDepthVP(DepthBiasMVP);


    Application::getInstance()->getShader(objectShaderId)->applyTexture(obj.getTextureId());
    Application::getInstance()->getShader(objectShaderId)->applyNormalTexture(obj.getNormalTextureId());


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