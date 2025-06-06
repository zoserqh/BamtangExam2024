#version 460 core

layout (location = 0) in vec2 vertex;

out vec3 ourColor;

uniform mat4 projection;
uniform vec2 translateXY;
uniform float scale;
uniform vec3 aColor;
void main()
{
    gl_Position = projection * vec4(scale*vertex + translateXY, 0.0, 1.0);
    ourColor = aColor;
}