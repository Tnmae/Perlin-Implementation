#version 330 core

out vec4 FragColor;
in vec3 position;

uniform sampler2D diffuse0;

void main()
{
    FragColor = vec4((position.y + position.z) / 3, (position.x + position.z) / 3, (position.x + position.y) / 3, 1.0f);
}
