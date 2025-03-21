/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <vector>
#include <iostream>
#include "hSource/game.h"
#include "hSource/resource_manager.h"

    float* piece1 = new float[480]{
    // positions            // colors
    -0.5f, 0.5f,        0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f,       0.5f, 0.5f, 0.5f,
    -0.375f, 0.5f,      0.5f, 0.5f, 0.5f,

    -0.375f, 0.5f,      0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f,       0.5f, 0.5f, 0.5f,
    -0.375f, -0.375f,   0.5f, 0.5f, 0.5f,

    -0.375f, -0.375f,   0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f,       0.5f, 0.5f, 0.5f,
    0.5f, -0.5f,        0.5f, 0.5f, 0.5f,

    0.5f, -0.5f,        0.5f, 0.5f, 0.5f,
    0.375f, -0.375f,    0.5f, 0.5f, 0.5f,
    -0.375f, -0.375f,   0.5f, 0.5f, 0.5f,

    0.375f, -0.375f,    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f,        0.5f, 0.5f, 0.5f,
    0.5f, 0.5f,         0.5f, 0.5f, 0.5f,

    0.5f, 0.5f,         0.5f, 0.5f, 0.5f,
    0.375f, 0.5f,       0.5f, 0.5f, 0.5f,
    0.375f, -0.375f,    0.5f, 0.5f, 0.5f,

    -0.375f, 0.5f,      1.0f, 0.586f, 0.0f,
    -0.375f, -0.375f,   1.0f, 0.586f, 0.0f,
    0.375f, -0.375f,    1.0f, 0.586f, 0.0f,

    0.375f, -0.375f,    1.0f, 0.586f, 0.0f,
    0.375f, 0.5f,       1.0f, 0.586f, 0.0f,
    -0.375f, 0.5f,      1.0f, 0.586f, 0.0f
    };

Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 

}

Game::~Game()
{

}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("../resources/shaders/piece_vs.glsl", "../resources/shaders/piece_fs.glsl", nullptr, "piece");
    ResourceManager::GetShader("piece").Use();
    
    // configure shaders
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model,glm::vec3(100.0f,100.0f,1.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    ResourceManager::GetShader("piece").SetMatrix4("model", model);

    glm::mat4 projection = glm::ortho(-1*static_cast<float>(this->Width)/2, static_cast<float>(this->Width)/2, 
                                      -1*static_cast<float>(this->Height)/2, static_cast<float>(this->Height)/2, -1.0f, 1.0f);
    ResourceManager::GetShader("piece").SetMatrix4("projection", projection);

    glm::vec2 pos(1,1);
    glm::vec2 size(50,50);
    glm::vec2 vel(0,0);
    float rot(0);
    GameObject* p = new GameObject(pos,size,vel,rot,piece1);
    pieces.push_back(p);

    // configure VAO/VBO
    unsigned int VBO;
    glGenVertexArrays(1, &VAOsPieces[0]);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAOsPieces[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    std::cout << "sizeof(piece1): "<< sizeof(piece1)<<"\n";
    glBufferData(GL_ARRAY_BUFFER, /*sizeof(piece1)*/480, piece1, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    std::cout << "ResourceManager::GetShader(\"piece\").ID: " << ResourceManager::GetShader("piece").ID << "\n";
    std::cout << "VAOsPieces[0]: " << VAOsPieces[0] << "\n";

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    if(this->State == GAME_ACTIVE)
    {
        // draw the maze once 
        ResourceManager::GetShader("piece").Use();
        glBindVertexArray(VAOsPieces[0]);
        glDrawArrays(GL_TRIANGLES, 0, 480/*sizeof(piece1)*/);
        //draw A
        //draw B
        //draw circle
    }
}

// for(int i=0;i<4;i++){
//     for(int j=0;j<4;j++){
//         std::cout << projection[i][j] << " ";
//     } std::cout << std::endl;
// }
// std::cout << "xD" << "\n";