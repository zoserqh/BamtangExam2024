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


Game::Game(unsigned int width, unsigned int height) 
    : state(GAME_ACTIVE), keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

void Game::Init()
{
    ResourceManager::LoadShader("../resources/shaders/gameObject_vs.glsl", "../resources/shaders/gameObject_fs.glsl", nullptr, "gameObject");

    //config letters
    int lengthDataLetterG = 66;
    float* dataLetterG = new float[lengthDataLetterG]{
        //coord
        // Parte superior
        0.20f, 0.48f,
        0.10f, 0.50f,
        0.00f, 0.50f,
        -0.10f, 0.50f,
        -0.20f, 0.48f,
        -0.30f, 0.45f,
        -0.35f, 0.42f,
        -0.40f, 0.38f,
        -0.43f, 0.34f,
        -0.46f, 0.30f,
        -0.48f, 0.25f,
        -0.50f, 0.20f, //12
        // Lado izquierdo
        -0.50f, -0.25f,
        -0.48f, -0.30f, //2
        // Parte inferior
        -0.46f, -0.35f,
        -0.43f, -0.39f,
        -0.40f, -0.42f,
        -0.35f, -0.45f,
        -0.30f, -0.47f,
        -0.25f, -0.49f,
        -0.20f, -0.50f,
        0.10f, -0.50f,
        0.15f, -0.49f,
        0.20f, -0.48f,
        0.25f, -0.46f,
        0.30f, -0.44f,
        0.35f, -0.41f,
        0.40f, -0.37f,
        0.45f, -0.32f, //15
        // Parte derecha
        0.48f, -0.27f,
        0.50f, -0.22f,
        0.50f, 0.03f, //3
        //Trazo horizontal de la G
        0.05f, 0.03f //1
    };
    
    letterG = new GameObject(glm::vec2(300.0f,300.0f), glm::vec3(0.0f,0.0f,1.0f), 50.0f, dataLetterG, lengthDataLetterG);
    letterG->configRender(Width,Height);
    delete [] dataLetterG;

    int lengthDataLetterV = 6;
    float* dataLetterV = new float[lengthDataLetterV]{
        //coord
        -0.4f, 0.5f,
        0.0f, -0.5f,
        0.4f, 0.5f
    };

    letterV = new GameObject(glm::vec2(-300.0f,-300.0f), glm::vec3(1.0f,0.6445f,0.0f), 50.0f, dataLetterV, lengthDataLetterV);
    letterV->configRender(Width,Height);
    delete [] dataLetterV;

    int lengthDataLetterO = 58;
    float* dataLetterO = new float[lengthDataLetterO]{
        //coord
        // Parte superior
        0.0, 0.5,
        0.15, 0.48,
        0.25, 0.44,
        0.35, 0.38,
        0.42, 0.30,
        0.47, 0.20,
        0.5, 0.10,
        0.5, 0.0,//8
        
        //Parte derecha
        0.5, -0.10,
        0.47, -0.20,
        0.42, -0.30,
        0.35, -0.38,
        0.25, -0.44,
        0.15, -0.48,
        0.0, -0.5,
        -0.15, -0.48,//8
        
        // Parte inferior
        -0.25, -0.44,
        -0.35, -0.38,
        -0.42, -0.30,
        -0.47, -0.20,
        -0.5, -0.10,
        -0.5, 0.0,//6
        
        //Parte izquierda
        -0.5, 0.10,
        -0.47, 0.20,
        -0.42, 0.30,
        -0.35, 0.38,
        -0.25, 0.44,
        -0.15, 0.48,
        0.0, 0.5,//7
    };
    
    letterO = new GameObject(glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.6445f,0.0f), 50.0f, dataLetterO, lengthDataLetterO);
    letterO->configRender(Width,Height);
    delete [] dataLetterO;
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    
}

void Game::Render()
{
    letterG->drawObject();
    letterV->drawObject();
    letterO->drawObject();
}

void Game::Reset()
{

}