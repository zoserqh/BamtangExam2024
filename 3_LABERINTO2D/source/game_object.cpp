/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "hSource/game_object.h"
#include "hSource/resource_manager.h"

GameObject::GameObject() 
    : position(0.0f, 0.0f), sideObject(1.0f), velocity(glm::vec2(0.0f)) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 posG, float sideObj, float modvel, float* dataO, int lenData) 
    : position(pos), posGraph(posG), sideObject(sideObj), modVelocity(modvel), dataObject(dataO), lengthData(lenData) { }

void GameObject::configRender(unsigned int Width, unsigned int Height)
{
    ResourceManager::GetShader("gameObject").Use();
    glm::mat4 projection = glm::ortho(-1*static_cast<float>(Width)/2, static_cast<float>(Width)/2, 
                                      -1*static_cast<float>(Height)/2, static_cast<float>(Height)/2, -1.0f, 1.0f);
    ResourceManager::GetShader("gameObject").SetMatrix4("projection", projection);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*lengthData, dataObject, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GameObject::drawObject() const
{
    ResourceManager::GetShader("gameObject").Use();
    ResourceManager::GetShader("gameObject").SetFloat("scale", sideObject);
    ResourceManager::GetShader("gameObject").SetVector2f("translateXY", position);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0,lengthData/5);
}