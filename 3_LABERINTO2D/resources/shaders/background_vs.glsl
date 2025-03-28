#version 460 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 projection;
uniform float scale;

void main()
{
    TexCoords = texCoords;
    gl_Position = projection * vec4(scale*vertex, 0.0, 1.0); 
}  