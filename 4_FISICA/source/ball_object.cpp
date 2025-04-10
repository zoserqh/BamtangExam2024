
#include "hSource/ball_object.h"

// velocity and time THRESHOLD
const float VELOCITY_THRESHOLD = 35.0f;
const float TIME_TO_DISAPPEAR = 0.5f;

BallObject::BallObject(glm::vec2 pos, glm::vec3 col, float sideObj,glm::vec2 vel, float elast, float frict, float* dataO, int lenData) : 
GameObject(pos,col,sideObj,dataO,lenData), velocity(vel), elasticity(elast), friction(frict)
{ 
    radius = sideObj/2;
    mass = M_PI * radius * radius; // mass is proportional to area
}

void BallObject::update(float deltaTime, float gravity, float windowWidth, float windowHeight) 
{   
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
    if (std::abs(velocity.x) < VELOCITY_THRESHOLD && std::abs(velocity.y) < VELOCITY_THRESHOLD &&
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

const glm::vec2& BallObject::getVelocity() const {
    return velocity;
}

float BallObject::getRadius() const {
    return radius;
}

float BallObject::getMass() const {
    return mass;
}

void BallObject::setVelocity(const glm::vec2& newVelocity){
    velocity = newVelocity;
}

bool BallObject::shouldBeRemoved() const { return isStatic && staticTimer <= 0; }

void resolveBallCollision(BallObject& ball1, BallObject& ball2) {
    glm::vec2 delta = ball2.getPosition() - ball1.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    
    if (distance < ball1.getRadius() + ball2.getRadius()) {
        // Normalizar la dirección de colisión
        glm::vec2 normal = delta / distance;
        
        // Calcular la profundidad de penetración
        float penetrationDepth = (ball1.getRadius() + ball2.getRadius() - distance) / 2.0f;
        
        // Separar las pelotas para evitar solapamiento
        glm::vec2 correction = normal * penetrationDepth;
        ball1.setPosition(ball1.getPosition() - correction);
        ball2.setPosition(ball2.getPosition() + correction);
        
        // Calcular velocidades relativas en la dirección normal
        glm::vec2 relativeVelocity = ball2.getVelocity() - ball1.getVelocity();
        float dotProduct = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;
        
        // Si las pelotas ya se están separando, no aplicamos el impulso
        if (dotProduct > 0) return;
        
        // Elijo la elasticidad menor para ser conservador
        float elasticity = 0.7f; // Podríamos usar el min de los dos objetos
        
        // Calcular el impulso
        float j = -(1.0f + elasticity) * dotProduct / 
                 (1.0f / ball1.getMass() + 1.0f / ball2.getMass());
        
        // Aplicar el impulso
        glm::vec2 impulse = normal * j;
        glm::vec2 ball1Impulse = impulse / ball1.getMass();
        glm::vec2 ball2Impulse = impulse / ball2.getMass();
        
        ball1.setVelocity(ball1.getVelocity() - ball1Impulse);
        ball2.setVelocity(ball2.getVelocity() + ball2Impulse);
    }
}