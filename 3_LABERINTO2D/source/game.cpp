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
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), maze(&mazeTarget)
{

}

Game::~Game()
{

}

void Game::Init()
{
    maze->configRender(Width,Height);
    // glm::vec2 pos(1,1);
    // glm::vec2 size(50,50);
    // glm::vec2 vel(0,0);
    // float rot(0);
    // GameObject* p = new GameObject(pos,size,vel,rot,piece1);
    // pieces.push_back(p);
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
        maze->drawMaze2D();
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