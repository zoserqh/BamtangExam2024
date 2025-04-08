
#include "hSource/ball_object.h"

BallObject::BallObject(glm::vec2 pos, glm::vec3 col, float sideObj,float vel, float* dataO, int lenData) : 
    GameObject(pos,col,sideObj,dataO,lenData), modVelocity(vel) 
    { }