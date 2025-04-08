#ifndef BALLOBJECT_H
#define BALLOBJECT_H


#include "game_object.h"

class BallObject : public GameObject {
public:
    float modVelocity;

    BallObject(glm::vec2 pos, glm::vec3 col, float sideObj,float vel, float* dataO, int lenData);
};

#endif