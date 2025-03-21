#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class GameObject
{
public:
    // object state
    glm::vec2   Position, Size, Velocity;
    float       Rotation;
    float*      pieceData;

    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, float rot, float* pData);
    // draw sprite
    // void Draw(SpriteRenderer &renderer);
};

#endif