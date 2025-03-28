#include <iostream>
#include "hSource/background.h"
#include "hSource/resource_manager.h"

Background::Background(glm::vec2 pos, float _side)
: position(pos), side(_side) { }

void Background::configRender(unsigned int Width, unsigned int Height)
{
    ResourceManager::GetShader("background").Use();
    glm::mat4 projection = glm::ortho(-1*static_cast<float>(Width)/2, static_cast<float>(Width)/2, 
                                      -1*static_cast<float>(Height)/2, static_cast<float>(Height)/2, -1.0f, 1.0f);
    ResourceManager::GetShader("background").SetMatrix4("projection", projection);
    ResourceManager::GetShader("background").SetInteger("screenTexture", 0);

    int lengthQuadData = 24;
    float* dataQuad = new float[lengthQuadData]{
        // positions        // texture Coords
        -0.5f, 0.5f,        0.0f, 1.0f,
        -0.5f, -0.5f,       0.0f, 0.0f,
        0.5f, 0.5f,         1.0f, 1.0f,
        0.5f, 0.5f,         1.0f, 1.0f,
        -0.5f, -0.5f,       0.0f, 0.0f,
        0.5f, -0.5f,        1.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*lengthQuadData, dataQuad, GL_STATIC_DRAW);
    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // textCoords attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    delete[] dataQuad;

    //frameBuffer
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    // create a color attachment texture
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
    }
    //unbind
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
void Background::drawBackground() const
{
    ResourceManager::GetShader("background").Use();
    ResourceManager::GetShader("background").SetFloat("scale", side);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}