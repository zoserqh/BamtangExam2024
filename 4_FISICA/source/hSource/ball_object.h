#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include<cmath>
#include "game_object.h"

class BallObject : public GameObject {
public:
    glm::vec2 velocity;
    float radius;
    float elasticity;
    float friction;
    bool isStatic;
    float staticTimer;
    float mass;

    BallObject(glm::vec2 pos, glm::vec3 col, float sideObj,glm::vec2 vel, float elast, float frict, float* dataO, int lenData);
    void update(float deltaTime, float gravity, float windowWidth, float windowHeight);
    void handleWallCollisions(float windowWidth, float windowHeight);

    const glm::vec2& getVelocity() const;
    float getRadius() const;
    float getMass() const;

    void setVelocity(const glm::vec2& newVelocity);

    bool shouldBeRemoved() const;
};

void resolveBallCollision(BallObject& ball1, BallObject& ball2);

#endif