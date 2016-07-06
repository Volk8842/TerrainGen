#version 330 core

in vec3 ver_color;

out vec4 color;

void main()
{
    color = vec4(ver_color, 1.0f);
}