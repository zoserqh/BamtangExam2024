#ifndef GAME_H
#define GAME_H

#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resource_manager.h"
#include "game_object.h"
#include "ball_object.h"
#include "arrow_object.h"
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
    bool                    buttonLeftCursorPressed = false;
    float                   cursorX;
    float                   cursorY;
    unsigned int            Width, Height;
    //elements
    GameObject* letterG;
    GameObject* letterV;
    GameObject* letterO;
    std::vector<BallObject*> balls;
    ArrowObject* arrowG;
    ArrowObject* arrowO;

    // constructor/destructor
    Game(unsigned int width, unsigned int height);
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