#include "hSource/game_object.h"

GameObject::GameObject(glm::vec2 pos, glm::vec3 col, float sideObj, float* dataO, int lenData) 
    : position(pos), color(col), sideObject(sideObj), dataObject(dataO), lengthData(lenData) 
{ 

}

const glm::vec2& GameObject::getPosition() const { 
    return position; 
}

void GameObject::setPosition(const glm::vec2& newPosition) { 
    position = newPosition; 
}

void GameObject::configRender(unsigned int Width, unsigned int Height)
{
    ResourceManager::GetShader("gameObject").Use();
    glm::mat4 projection = glm::ortho(-1*static_cast<float>(Width)/2, static_cast<float>(Width)/2, 
                                      -1*static_cast<float>(Height)/2, static_cast<float>(Height)/2, -1.0f, 1.0f);
    ResourceManager::GetShader("gameObject").SetMatrix4("projection", projection);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*lengthData, dataObject, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GameObject::drawObject() const
{
    ResourceManager::GetShader("gameObject").Use();
    ResourceManager::GetShader("gameObject").SetFloat("scale", sideObject);
    ResourceManager::GetShader("gameObject").SetVector2f("translateXY", position);
    ResourceManager::GetShader("gameObject").SetVector3f("aColor", color);
    glBindVertexArray(VAO);
    glLineWidth(3.0f);
    glEnable(GL_LINE_SMOOTH);
    glDrawArrays(GL_LINE_STRIP, 0,lengthData/2);
}