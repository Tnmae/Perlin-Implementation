#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 color;

uniform float gMaxHeight;
uniform float gMinHeight;
uniform mat4 camera_matrix;
uniform mat4 model;

void main() {
    gl_Position = camera_matrix * model * vec4(aPos, 1.0f);
    float deltaHeight = gMaxHeight - gMinHeight;
    float heightRatio = (aPos.y - gMinHeight) / deltaHeight;
    float c = heightRatio * 0.8 + 0.2;
    color = vec3(c, c, c);
}
