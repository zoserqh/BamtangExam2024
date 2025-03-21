/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "hSource/game_object.h"

GameObject::GameObject() 
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Rotation(0.0f), pieceData(NULL){ }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, float rot, float* pData) 
    : Position(pos), Size(size), Velocity(velocity), Rotation(rot), pieceData(pData){ }

// void GameObject::Draw(SpriteRenderer &renderer)
// {
//     renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
// }