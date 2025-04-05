#include "game_object.h"

class ArrowObject : public GameObject {
public:
    float angle;
    
    ArrowObject(glm::vec2 pos, glm::vec3 col, float sideObj, float _angle, float* dataO, int lenData) : 
    GameObject(pos,col,sideObj,dataO,lenData), angle(_angle) 
    {}
};