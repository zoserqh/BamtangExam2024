#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class GameObject
{
public:
    // render
    glm::vec2   position, velocity;
    float sideObject;
    float* dataObject;
    int lengthData;
    unsigned int VBO;
    unsigned int VAO;
    GameObject();
    GameObject(glm::vec2 pos, float sideObj, glm::vec2 vel, float* dataO, int lenData);
    
    // render
    void configRender(unsigned int Width, unsigned int Height);
    void drawObject() const;
};

#endif