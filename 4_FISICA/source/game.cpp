#include <vector>
#include <iostream>
#include "hSource/game.h"
#include <cmath>

 // physic parameters
 float gravityValue = 980.0f; // pixeles/s²
 float elasticityValue = 0.7f;
 float frictionValue = 0.05f;

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
    ResourceManager::LoadShader("../resources/shaders/arrowObject_vs.glsl", "../resources/shaders/arrowObject_fs.glsl", nullptr, "arrowObject");

    //config cannon
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
    
    letterO = new GameObject(glm::vec2(100.0f,-100.0f), glm::vec3(1.0f,0.6445f,0.0f), 20.0f, dataLetterO, lengthDataLetterO);
    letterO->configRender(Width,Height);
    delete [] dataLetterO;
    
    int lengthDataArrowO = 10;
    float* dataArrowO = new float[lengthDataArrowO]{
        -0.125f, 0.25f,
        0.0f, 0.5f,
        0.0f, -0.5f,
        0.0f, 0.5f,
        0.125f, 0.25f,
    };

    arrowO = new ArrowObject(glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), 50.0f, 315.0f, dataArrowO, lengthDataArrowO);
    arrowO->position = glm::vec2(letterO->position.x,letterO->position.y);
    arrowO->configRender(Width,Height);
    delete [] dataArrowO;

    int lengthDataLetterV = 6;
    float* dataLetterV = new float[lengthDataLetterV]{
        //coord
        -0.4f, 0.5f,
        0.0f, -0.5f,
        0.4f, 0.5f
    };

    float vPosx = letterO->position.x + (arrowO->sideObject)*cos(arrowO->angle*(M_PI/180)+M_PI/2) - arrowO->sideObject*sqrt(2)/16;
    float vPosy = letterO->position.y + (arrowO->sideObject)*sin(arrowO->angle*(M_PI/180)+M_PI/2) + arrowO->sideObject*sqrt(2)/16;
    letterV = new GameObject(glm::vec2(vPosx,vPosy), glm::vec3(1.0f,0.6445f,0.0f), 10.0f, dataLetterV, lengthDataLetterV);
    letterV->configRender(Width,Height);
    delete [] dataLetterV;

    // config vector gravity
    int lengthDataArrowG = 10;
    float* dataArrowG = new float[lengthDataArrowG]{
        -0.25f, 0.25f,
        0.0f, 0.5f,
        0.0f, -0.5f,
        0.0f, 0.5f,
        0.25f, 0.25f,
    };

    arrowG = new ArrowObject(glm::vec2(350.0f,375.0f), glm::vec3(0.0f,0.0f,1.0f), 50.0f, 180.0f, dataArrowG, lengthDataArrowG);
    arrowG->configRender(Width,Height);
    delete [] dataArrowG;

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
    
    letterG = new GameObject(glm::vec2(330.0f,360.0f), glm::vec3(0.0f,0.0f,1.0f), 20.0f, dataLetterG, lengthDataLetterG);
    letterG->configRender(Width,Height);
    delete [] dataLetterG;

}

void Game::Update(float dt)
{   if(state == GAME_ACTIVE){
        for(int i=0;i<balls.size();i++){
            balls[i]->update(dt,gravityValue,Width,Height);
            // Check for collisions with other balls
            for (size_t j = i + 1; j < balls.size(); ++j) {
                resolveBallCollision(*balls[i], *balls[j]);
            }
        }

        // delete static balls
        for(int i=0;i<balls.size();i++){
            if(balls[i]->shouldBeRemoved()) {
                delete balls[i];
                balls.erase(balls.begin()+i);
                break;
            }
        }
    }
}

void Game::ProcessInput(float dt){
    if(state == GAME_ACTIVE){
        if(buttonLeftCursorPressed){
            letterO->position.x = cursorX - Width/2;
            letterO->position.y = Height/2 - cursorY;

            //
            arrowO->position = glm::vec2(letterO->position.x,letterO->position.y);

            //set letterV position
            float vPosx = letterO->position.x + (arrowO->sideObject)*cos(arrowO->angle*(M_PI/180)+M_PI/2) - arrowO->sideObject*sqrt(2)/16;
            float vPosy = letterO->position.y + (arrowO->sideObject)*sin(arrowO->angle*(M_PI/180)+M_PI/2) + arrowO->sideObject*sqrt(2)/16;
            letterV->position = glm::vec2(vPosx, vPosy);

            buttonLeftCursorPressed = false;
        }

        if(keys[GLFW_KEY_W]){
            arrowO->angle += 2;
            
            //set letterV position
            float vPosx = letterO->position.x + (arrowO->sideObject)*cos(arrowO->angle*(M_PI/180)+M_PI/2) - arrowO->sideObject*sqrt(2)/16;
            float vPosy = letterO->position.y + (arrowO->sideObject)*sin(arrowO->angle*(M_PI/180)+M_PI/2) + arrowO->sideObject*sqrt(2)/16;
            letterV->position = glm::vec2(vPosx, vPosy);
        }
        else if(keys[GLFW_KEY_S]){
            arrowO->angle -= 2;
            
            //set letterV position
            float vPosx = letterO->position.x + (arrowO->sideObject)*cos(arrowO->angle*(M_PI/180)+M_PI/2) - arrowO->sideObject*sqrt(2)/16;
            float vPosy = letterO->position.y + (arrowO->sideObject)*sin(arrowO->angle*(M_PI/180)+M_PI/2) + arrowO->sideObject*sqrt(2)/16;
            letterV->position = glm::vec2(vPosx, vPosy);
        }
        else if(keys[GLFW_KEY_A]){
            if(arrowO->sideObject >0){
                arrowO->sideObject -= 2;
            } else {
                arrowO->sideObject = 0;
            }
            //set letterV position
            float vPosx = letterO->position.x + (arrowO->sideObject)*cos(arrowO->angle*(M_PI/180)+M_PI/2) - arrowO->sideObject*sqrt(2)/16;
            float vPosy = letterO->position.y + (arrowO->sideObject)*sin(arrowO->angle*(M_PI/180)+M_PI/2) + arrowO->sideObject*sqrt(2)/16;
            letterV->position = glm::vec2(vPosx, vPosy);
        }
        else if(keys[GLFW_KEY_D]){
            if(arrowO->sideObject <100){
                arrowO->sideObject += 2;
            } else {
                arrowO->sideObject = 100;
            }
            //set letterV position
            float vPosx = letterO->position.x + (arrowO->sideObject)*cos(arrowO->angle*(M_PI/180)+M_PI/2) - arrowO->sideObject*sqrt(2)/16;
            float vPosy = letterO->position.y + (arrowO->sideObject)*sin(arrowO->angle*(M_PI/180)+M_PI/2) + arrowO->sideObject*sqrt(2)/16;
            letterV->position = glm::vec2(vPosx, vPosy);
        }
        else if(keys[GLFW_KEY_SPACE]){
            int lengthDataBall = 66;
            float* dataBall = new float[lengthDataBall]{
                0.5, 0.0,
                0.4904, 0.0975,
                0.4619, 0.1913,
                0.4157, 0.2778,
                0.3536, 0.3536,
                0.2778, 0.4157,
                0.1913, 0.4619,
                0.0975, 0.4904,
                0.0, 0.5,
                -0.0975, 0.4904,
                -0.1913, 0.4619,
                -0.2778, 0.4157,
                -0.3536, 0.3536,
                -0.4157, 0.2778,
                -0.4619, 0.1913,
                -0.4904, 0.0975,
                -0.5, 0.0,
                -0.4904, -0.0975,
                -0.4619, -0.1913,
                -0.4157, -0.2778,
                -0.3536, -0.3536,
                -0.2778, -0.4157,
                -0.1913, -0.4619,
                -0.0975, -0.4904,
                0.0, -0.5,
                0.0975, -0.4904,
                0.1913, -0.4619,
                0.2778, -0.4157,
                0.3536, -0.3536,
                0.4157, -0.2778,
                0.4619, -0.1913,
                0.4904, -0.0975,
                0.5, 0.0
            };

            
            BallObject* ball = new BallObject(letterO->position, 
                                            glm::vec3(0.0f,0.0f,0.0f), 
                                            100.0f, 
                                            glm::vec2( 10*(arrowO->sideObject)*cos(arrowO->angle*(M_PI/180)+M_PI/2) ,10*(arrowO->sideObject)*sin(arrowO->angle*(M_PI/180)+M_PI/2)), 
                                            elasticityValue,
                                            frictionValue,
                                            dataBall, 
                                            lengthDataBall);
            ball->configRender(Width,Height);
            delete [] dataBall;
            balls.push_back(ball);
            keys[GLFW_KEY_SPACE] = false;
            std::cout << "balls.size(): " << balls.size() << "\n";
        }
    }
    
}

void Game::Render()
{   
    if(state == GAME_ACTIVE)
    {
        //
        letterO->drawObject();
        arrowO->drawObject();
        letterV->drawObject();

        //
        for(int i=0;i<balls.size();i++){
            balls[i]->drawObject();
        }
        
        //
        letterG->drawObject();
        arrowG->drawObject();
    }
    
}

void Game::Reset()
{

}