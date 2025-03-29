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


Game::Game(unsigned int width, unsigned int height, Maze& mazeTarget) 
    : state(GAME_ACTIVE), keys(), Width(width), Height(height), maze(&mazeTarget)
{

}

Game::~Game()
{

}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("../resources/shaders/piece_vs.glsl", "../resources/shaders/piece_fs.glsl", nullptr, "piece");
    ResourceManager::LoadShader("../resources/shaders/gameObject_vs.glsl", "../resources/shaders/gameObject_fs.glsl", nullptr, "gameObject");
    ResourceManager::LoadShader("../resources/shaders/background_vs.glsl", "../resources/shaders/background_fs.glsl", nullptr, "background");

    //config Maze
    maze->configRender(Width,Height);

    //config letters
    int lengthDataLetterA = 105;
    float* dataLetterA = new float[lengthDataLetterA]{
        // positions            // colors
        -0.125f, 0.5f,        0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f,         0.5f, 0.5f, 0.5f,
        -0.328125f, -0.5f,    0.5f, 0.5f, 0.5f,

        -0.125f, 0.5f,        0.5f, 0.5f, 0.5f,
        -0.328125f, -0.5f,    0.5f, 0.5f, 0.5f,
        0.0f, 0.375f,         0.5f, 0.5f, 0.5f,

        -0.1875f, -0.125f,    0.5f, 0.5f, 0.5f,
        -0.28125f, -0.375f,   0.5f, 0.5f, 0.5f,
        0.1875f, -0.125f,     0.5f, 0.5f, 0.5f,

        0.1875f, -0.125f,     0.5f, 0.5f, 0.5f,
        -0.28125f, -0.375f,   0.5f, 0.5f, 0.5f,
        0.28125f, -0.375f,    0.5f, 0.5f, 0.5f,
        
        0.125f, 0.5f,         0.5f, 0.5f, 0.5f,
        0.0f, 0.375f,         0.5f, 0.5f, 0.5f,
        0.328125f, -0.5f,     0.5f, 0.5f, 0.5f,

        0.328125f, -0.5f,     0.5f, 0.5f, 0.5f,
        0.5f, -0.5f,          0.5f, 0.5f, 0.5f,
        0.125f, 0.5f,         0.5f, 0.5f, 0.5f,

        0.125f, 0.5f,         0.5f, 0.5f, 0.5f,
        -0.125f, 0.5f,        0.5f, 0.5f, 0.5f,
        0.0f, 0.375f,         0.5f, 0.5f, 0.5f,
    };

    int lengthDataLetterB = 240;
    float* dataLetterB = new float[lengthDataLetterB]{
        // positions            // colors
        -0.5f, 0.5f,            0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f,           0.5f, 0.5f, 0.5f,
        -0.25f, -0.375f,        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f,           0.5f, 0.5f, 0.5f,
        0.125f, -0.5f,          0.5f, 0.5f, 0.5f,
        -0.25f, -0.375f,        0.5f, 0.5f, 0.5f,

        0.125f, -0.5f,          0.5f, 0.5f, 0.5f,
        0.375f, -0.375f,        0.5f, 0.5f, 0.5f,
        -0.25f, -0.375f,        0.5f, 0.5f, 0.5f,

        0.375f, -0.375f,        0.5f, 0.5f, 0.5f,
        0.125f, -0.25f,         0.5f, 0.5f, 0.5f,
        0.0f, -0.375f,          0.5f, 0.5f, 0.5f,

        0.125f, -0.25f,         0.5f, 0.5f, 0.5f,
        0.375f, -0.375f,        0.5f, 0.5f, 0.5f,
        0.375f, -0.125f,        0.5f, 0.5f, 0.5f,

        0.125f, -0.25f,         0.5f, 0.5f, 0.5f,
        0.375f, -0.125f,        0.5f, 0.5f, 0.5f,
        0.125f, 0.0f,           0.5f, 0.5f, 0.5f,

        0.125f, -0.25f,         0.5f, 0.5f, 0.5f,
        0.125f, 0.25f,          0.5f, 0.5f, 0.5f,
        0.0f, -0.125f,          0.5f, 0.5f, 0.5f,

        0.0f, -0.125f,          0.5f, 0.5f, 0.5f,
        0.125f, 0.25f,          0.5f, 0.5f, 0.5f,
        0.0f, 0.125f,           0.5f, 0.5f, 0.5f,

        0.0f, 0.125f,           0.5f, 0.5f, 0.5f,
        -0.25f, 0.125f,         0.5f, 0.5f, 0.5f,
        0.0f, -0.125f,          0.5f, 0.5f, 0.5f,

        0.0f, -0.125f,          0.5f, 0.5f, 0.5f,
        -0.25f, 0.125f,         0.5f, 0.5f, 0.5f,
        -0.25f, -0.125f,        0.5f, 0.5f, 0.5f,

        0.125f, 0.25f,          0.5f, 0.5f, 0.5f,
        0.125f, 0.0f,           0.5f, 0.5f, 0.5f,
        0.375f, 0.125f,         0.5f, 0.5f, 0.5f,

        0.125f, 0.25f,          0.5f, 0.5f, 0.5f,
        0.375f, 0.125f,         0.5f, 0.5f, 0.5f,
        0.375f, 0.375f,         0.5f, 0.5f, 0.5f,

        0.125f, 0.25f,          0.5f, 0.5f, 0.5f,
        0.375f, 0.375f,         0.5f, 0.5f, 0.5f,
        0.0f, 0.375f,           0.5f, 0.5f, 0.5f,

        0.375f, 0.375f,         0.5f, 0.5f, 0.5f,
        0.125f, 0.5f,           0.5f, 0.5f, 0.5f,
        -0.25f, 0.375f,         0.5f, 0.5f, 0.5f,

        0.125f, 0.5f,           0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,            0.5f, 0.5f, 0.5f,
        -0.25f, 0.375f,         0.5f, 0.5f, 0.5f,

        -0.25f, 0.375f,         0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,            0.5f, 0.5f, 0.5f,
        -0.25f, -0.375f,        0.5f, 0.5f, 0.5f,
    };

    float sideLetter = maze->sidePiece*0.7;
    float posxA =-(maze->getDimension()-1.0)*(maze->sidePiece)/2.0 + (maze->sidePiece)*(maze->getStartPosition()[0]);
    float posyA =(maze->getDimension()-1.0)*(maze->sidePiece)/2.0 - (maze->sidePiece)*(maze->getStartPosition()[1]);

    float posxB =-(maze->getDimension()-1.0)*(maze->sidePiece)/2.0 + (maze->sidePiece)*(maze->getFinalPosition()[0]);
    float posyB =(maze->getDimension()-1.0)*(maze->sidePiece)/2.0 - (maze->sidePiece)*(maze->getFinalPosition()[1]);

    glm::vec2 posA(posxA,posyA);
    glm::vec2 posB(posxB,posyB);
    glm::vec2 posGraphA(maze->getStartPosition()[0],maze->getStartPosition()[1]);
    glm::vec2 posGraphB(maze->getFinalPosition()[0],maze->getFinalPosition()[1]);

    letterA = new GameObject(posA, posGraphA, sideLetter, 0.0f, dataLetterA, lengthDataLetterA);
    letterB = new GameObject(posB, posGraphB, sideLetter, 0.0f, dataLetterB, lengthDataLetterB);
    
    letterA->configRender(Width,Height);
    letterB->configRender(Width,Height);

    delete [] dataLetterA;
    delete [] dataLetterB;
    
    //config mazeBackground
    float totalside;
    Width <= Height ? totalside=Width : totalside=Height;
    mazeBackground = new Background(glm::vec2(0.0f,0.0f), totalside);
    mazeBackground->configRender(Width,Height);

    //config Circle
    int lengthDataCircle = 480;
    float* dataCircle = new float[lengthDataCircle]{
        // positions            // colors
        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.5f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.490393f, 0.0975452f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.490393f, 0.0975452f,  0.0f, 0.0f, 1.0f,
        0.46194f, 0.191342f,    0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.46194f, 0.191342f,    0.0f, 0.0f, 1.0f,
        0.415735f, 0.277785f,   0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.415735f, 0.277785f,   0.0f, 0.0f, 1.0f,
        0.353553f, 0.353553f,   0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.353553f, 0.353553f,   0.0f, 0.0f, 1.0f,
        0.277785f, 0.415735f,   0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.277785f, 0.415735f,   0.0f, 0.0f, 1.0f,
        0.191342f, 0.46194f,    0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.191342f, 0.46194f,    0.0f, 0.0f, 1.0f,
        0.0975451f, 0.490393f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.0975451f, 0.490393f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.5f,             0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.0f, 0.5f,             0.0f, 0.0f, 1.0f,
        -0.0975452f, 0.490393f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.0975452f, 0.490393f, 0.0f, 0.0f, 1.0f,
        -0.191342f, 0.46194f,   0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.191342f, 0.46194f,   0.0f, 0.0f, 1.0f,
        -0.277785f, 0.415735f,  0.0f, 0.0f, 1.0f,
        
        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.277785f, 0.415735f,  0.0f, 0.0f, 1.0f,
        -0.353553f, 0.353553f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.353553f, 0.353553f,  0.0f, 0.0f, 1.0f,
        -0.415735f, 0.277785f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.415735f, 0.277785f,  0.0f, 0.0f, 1.0f,
        -0.46194f, 0.191342f,   0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.46194f, 0.191342f,   0.0f, 0.0f, 1.0f,
        -0.490393f, 0.0975452f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.490393f, 0.0975452f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.0f,            0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.5f, 0.0f,            0.0f, 0.0f, 1.0f,
        -0.490393f, -0.0975452f,0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.490393f, -0.0975452f,0.0f, 0.0f, 1.0f,
        -0.46194f, -0.191342f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.46194f, -0.191342f,  0.0f, 0.0f, 1.0f,
        -0.415735f, -0.277785f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.415735f, -0.277785f, 0.0f, 0.0f, 1.0f,
        -0.353553f, -0.353553f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.353553f, -0.353553f, 0.0f, 0.0f, 1.0f,
        -0.277785f, -0.415735f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.277785f, -0.415735f, 0.0f, 0.0f, 1.0f,
        -0.191342f, -0.46194f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.191342f, -0.46194f,  0.0f, 0.0f, 1.0f,
        -0.0975452f, -0.490393f,0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        -0.0975452f, -0.490393f,0.0f, 0.0f, 1.0f,
        0.0f, -0.5f,            0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.0f, -0.5f,            0.0f, 0.0f, 1.0f,
        0.0975452f, -0.490393f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.0975452f, -0.490393f, 0.0f, 0.0f, 1.0f,
        0.191342f, -0.46194f,   0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.191342f, -0.46194f,   0.0f, 0.0f, 1.0f,
        0.277785f, -0.415735f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.277785f, -0.415735f,  0.0f, 0.0f, 1.0f,
        0.353554f, -0.353553f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.353554f, -0.353553f,  0.0f, 0.0f, 1.0f,
        0.415735f, -0.277785f,  0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.415735f, -0.277785f,  0.0f, 0.0f, 1.0f,
        0.46194f, -0.191342f,   0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.46194f, -0.191342f,   0.0f, 0.0f, 1.0f,
        0.490393f, -0.0975451f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f,             0.0f, 0.0f, 1.0f,
        0.490393f, -0.0975451f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f,             0.0f, 0.0f, 1.0f,
    };
    
    float sideCircle = maze->sidePiece*0.9;
    float posxC =-(maze->getDimension()-1.0)*(maze->sidePiece)/2.0 + (maze->sidePiece)*(maze->getStartPosition()[0]);
    float posyC =(maze->getDimension()-1.0)*(maze->sidePiece)/2.0 - (maze->sidePiece)*(maze->getStartPosition()[1]);
    glm::vec2 posC(posxC,posyC);
    glm::vec2 posGraphC(maze->getStartPosition()[0],maze->getStartPosition()[1]);
    float moduleVelocityCircle = maze->sidePiece*4.0f;
    circle = new GameObject(posC, posGraphC, sideCircle, moduleVelocityCircle, dataCircle, lengthDataCircle);
    circle->configRender(Width,Height);
    delete [] dataCircle;

}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    if(state == GAME_ACTIVE){
        if(keys[GLFW_KEY_A]){
            if(maze->getCellType(circle->posGraph.x,circle->posGraph.y-1) == cellType::PATH){
                circle->position.x -= circle->modVelocity*dt;
            }
            float leftLimit = -(maze->getDimension()-1.0)*(maze->sidePiece)/2.0 + (maze->sidePiece)*(circle->posGraph.y-1);
            if(circle->position.x <= leftLimit){
                circle->posGraph.y--;
                circle->position.x = leftLimit; 
            }
        }
        else if(keys[GLFW_KEY_S]){
            if(maze->getCellType(circle->posGraph.x+1,circle->posGraph.y) == cellType::PATH){
                circle->position.y -= circle->modVelocity*dt;
            }
            float downLimit = (maze->getDimension()-1.0)*(maze->sidePiece)/2.0 - (maze->sidePiece)*(circle->posGraph.x+1);
            if(circle->position.y <= downLimit){
                circle->posGraph.x++;
                circle->position.y = downLimit; 
            }
        }
        else if(keys[GLFW_KEY_D]){
            if(maze->getCellType(circle->posGraph.x,circle->posGraph.y+1) == cellType::PATH){
                circle->position.x += circle->modVelocity*dt;
            }
            float rightLimit = -(maze->getDimension()-1.0)*(maze->sidePiece)/2.0 + (maze->sidePiece)*(circle->posGraph.y+1);
            if(circle->position.x >= rightLimit){
                circle->posGraph.y++;
                circle->position.x = rightLimit; 
            }
        }
        else if(keys[GLFW_KEY_W]){
            if(maze->getCellType(circle->posGraph.x-1,circle->posGraph.y) == cellType::PATH){
                circle->position.y += circle->modVelocity*dt;
            }
            float upLimit = (maze->getDimension()-1.0)*(maze->sidePiece)/2.0 - (maze->sidePiece)*(circle->posGraph.x-1);
            if(circle->position.y >= upLimit){
                circle->posGraph.x--;
                circle->position.y = upLimit; 
            }
        }
    }
}

void Game::Render()
{
    if(this->state == GAME_ACTIVE)
    {
        // draw the maze and letters once
        static int  key = 1;
        if(key == 1){
            glBindFramebuffer(GL_FRAMEBUFFER, mazeBackground->frameBuffer);
            maze->drawMaze2D();
            letterA->drawObject();
            letterB->drawObject();
            
            //free up memory in GPU
            for(int i =0;i<5;i++){
                glDeleteVertexArrays(1, &maze->VAOsPieces[i]);
                glDeleteBuffers(1, &maze->VBOsPieces[i]);
            }
            glDeleteVertexArrays(1, &letterA->VAO);
            glDeleteBuffers(1, &letterB->VBO);

            key++;
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw background
        mazeBackground->drawBackground();
        
        //draw circle
        circle->drawObject();
    }
}