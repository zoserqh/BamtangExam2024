#version 460 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 projection;
uniform float angle;
uniform float scale;
uniform vec2 translateXY;

const float PI = 3.1415926535897932384626433832795;

mat4 rotateZ(float a) {
  mat4 rotationMatrix;
  rotationMatrix[0] = vec4(cos(a), sin(a), 0, 0);
  rotationMatrix[1] = vec4(-sin(a), cos(a), 0, 0);
  rotationMatrix[2] = vec4(0, 0, 1, 0);
  rotationMatrix[3] = vec4(0, 0, 0, 1);
  return rotationMatrix;
}

mat4 scaleTranslateXY(float scale, vec2 v) {
  mat4 scaleMatrix;
  scaleMatrix[0] = vec4(scale, 0, 0, 0);
  scaleMatrix[1] = vec4(0, scale, 0, 0);
  scaleMatrix[2] = vec4(0, 0, 1, 0);
  scaleMatrix[3] = vec4(v.x, v.y, 0, 1);
  return scaleMatrix;
}

void main()
{
    float angleRadians = angle * PI / 180.0;
    mat4 model = scaleTranslateXY(scale, translateXY) * rotateZ(angleRadians);
    gl_Position = projection * model * vec4(vertex, 0.0, 1.0);
    ourColor = aColor;
}