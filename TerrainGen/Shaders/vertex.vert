#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 view;
uniform mat4 projection;

out vec3 ver_color;

void main()
{
	vec4 model = translation * rotation * scale * vec4(position, 1.0f);
    gl_Position = projection * view * model;
	ver_color = color;
}