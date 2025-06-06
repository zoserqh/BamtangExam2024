/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game_object.h"
#include "background.h"
#include "maze.h"
#include "shader.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    // game state
    GameState               state;	
    bool                    keys[1024];
    unsigned int            Width, Height;
    int mazeDimension = 5;
    bool drawOnceKey = true;
    //elements
    Maze* maze;
    GameObject* letterA;
    GameObject* letterB;
    Background* mazeBackground;
    GameObject* circle;

    // constructor/destructor
    Game(unsigned int width, unsigned int height,int mazeD);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void Reset();
};

#endif