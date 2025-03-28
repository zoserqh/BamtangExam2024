#version 460 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D backgroundTexture;

void main()
{
    vec3 col = texture(backgroundTexture, TexCoords).rgb;
    FragColor = vec4(col, 1.0);
} 