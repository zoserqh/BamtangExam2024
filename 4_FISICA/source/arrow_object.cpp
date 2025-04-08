
#include "hSource/arrow_object.h"

ArrowObject::ArrowObject(glm::vec2 pos, glm::vec3 col, float sideObj, float _angle, float* dataO, int lenData) : 
    GameObject(pos,col,sideObj,dataO,lenData), angle(_angle) 
    {}

void ArrowObject::configRender(unsigned int Width, unsigned int Height){
    ResourceManager::GetShader("arrowObject").Use();
    glm::mat4 projection = glm::ortho(-1*static_cast<float>(Width)/2, static_cast<float>(Width)/2, 
                                      -1*static_cast<float>(Height)/2, static_cast<float>(Height)/2, -1.0f, 1.0f);
    ResourceManager::GetShader("arrowObject").SetMatrix4("projection", projection);

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

void ArrowObject::drawObject() const {
    ResourceManager::GetShader("arrowObject").Use();
    ResourceManager::GetShader("arrowObject").SetFloat("scale", sideObject);
    ResourceManager::GetShader("arrowObject").SetVector2f("translateXY", position);
    ResourceManager::GetShader("arrowObject").SetFloat("angle", angle);
    ResourceManager::GetShader("arrowObject").SetVector3f("aColor", color);
    glBindVertexArray(VAO);
    glLineWidth(3.0f);
    glEnable(GL_LINE_SMOOTH);
    glDrawArrays(GL_LINE_STRIP, 0,lengthData/2);
}