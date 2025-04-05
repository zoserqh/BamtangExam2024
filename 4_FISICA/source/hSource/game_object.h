#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class GameObject
{
public:
    glm::vec2   position;
    glm::vec3 color;
    float sideObject;
    float* dataObject;
    int lengthData;
    unsigned int VBO;
    unsigned int VAO;
    GameObject(glm::vec2 pos, glm::vec3 col, float sideObj, float* dataO, int lenData);
    
    // render
    virtual void configRender(unsigned int Width, unsigned int Height);
    virtual void drawObject() const;
};

#endif