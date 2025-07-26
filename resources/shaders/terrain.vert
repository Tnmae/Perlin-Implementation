#version 330 core

layout(location = 0) vec3 aPos;
layout(location = 1) vec3 aColor;

out vec3 color;

uniform mat4 camera_matrix;
uniform mat4 model;

void main() {
    gl_Position = camera_matrix * model * vec4(aPos, 1.0f);
    color = aColor;
}
