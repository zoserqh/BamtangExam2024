#ifndef ARROWOBJECT_H
#define ARROWOBJECT_H

#include "game_object.h"

class ArrowObject : public GameObject {
public:
    float angle;
    ArrowObject(glm::vec2 pos, glm::vec3 col, float sideObj, float _angle, float* dataO, int lenData);
    
    //render
    void configRender(unsigned int Width, unsigned int Height);
    void drawObject() const;
};

#endif