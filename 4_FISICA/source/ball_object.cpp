
#include "hSource/ball_object.h"
#include<iostream>

// physic constants
const float STATIC_THRESHOLD = 10.0f; // velocidad por debajo de la cual las pelotas se consideran inmóviles
const float TIME_TO_DISAPPEAR = 1.0f; // tiempo en segundos que una pelota permanece inmóvil antes de desaparecer

BallObject::BallObject(glm::vec2 pos, glm::vec3 col, float sideObj,glm::vec2 vel, float elast, float frict, float* dataO, int lenData) : 
GameObject(pos,col,sideObj,dataO,lenData), velocity(vel), elasticity(elast), friction(frict)
{ 
    radius = sideObj/2;
    mass = M_PI * radius * radius; // mass is proportional to area
}

void BallObject::update(float deltaTime, float gravity, float windowWidth, float windowHeight) 
{   
    // std::cout << "pos: " << position.x << ", " << position.y << "\n";
    // std::cout << "vel: " << velocity.x << ", " << velocity.y << "\n\n";
    
    velocity.y -= gravity * deltaTime;

    
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Collision with walls
    handleWallCollisions(windowWidth, windowHeight);

    // fricción when tha ball touch the floor
    if (std::abs(position.y - radius + windowHeight/2) < 1.0f) {
        velocity.x *= (1.0f - friction);
    }

    // Verify if motionless
    if (std::abs(velocity.x) < STATIC_THRESHOLD && std::abs(velocity.y) < STATIC_THRESHOLD &&
        position.y - radius < -windowHeight/2 + 2.0f) {
        if (!isStatic) {
            isStatic = true;
            staticTimer = TIME_TO_DISAPPEAR;
        } else {
            staticTimer -= deltaTime;
        }
    } else {
        isStatic = false;
    }
}

void BallObject::handleWallCollisions(float windowWidth, float windowHeight) 
{
    // collision with the right wall
    if (position.x + radius > windowWidth/2) {
        position.x = windowWidth/2 - radius;
        velocity.x = -velocity.x * elasticity;
    }

    // collision with the left wall
    if (position.x - radius < -windowWidth/2) {
        position.x = -windowWidth/2 + radius;
        velocity.x = -velocity.x * elasticity;
    }

    // collision with the ground
    if (position.y - radius < -windowHeight/2) {
        position.y = -windowHeight/2 + radius;
        velocity.y = -velocity.y * elasticity;
    }

    // collision with the roof
    if (position.y + radius > windowHeight/2) {
        position.y = windowHeight/2 - radius;
        velocity.y = -velocity.y * elasticity;
    }
}

bool BallObject::shouldBeRemoved() const { return isStatic && staticTimer <= 0; }