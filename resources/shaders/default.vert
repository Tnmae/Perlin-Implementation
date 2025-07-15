#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTex;

out vec2 texCoords;

uniform mat4 camera_matrix;
uniform mat4 model;

void main()
{
    gl_Position = camera_matrix * model * vec4(aPos, 1.0f);
    texCoords = aTex;
}
