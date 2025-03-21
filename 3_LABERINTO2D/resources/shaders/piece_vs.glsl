#version 460 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(vertex, 0.0, 1.0);
    //gl_Position = model * vec4(vertex, 0.0, 1.0);
    //gl_Position = vec4(vertex, 0.0, 1.0) ;
    ourColor = aColor;
}