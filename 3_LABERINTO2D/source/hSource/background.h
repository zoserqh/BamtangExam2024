
#include <glm/glm.hpp>

class Background 
{
public:

    glm::vec2   position;
    float side;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int frameBuffer;
    unsigned int textureColorbuffer;

    Background(glm::vec2 pos, float _side);
    void configRender(unsigned int Width, unsigned int Height);
    void drawBackground() const;

};