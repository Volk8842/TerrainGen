#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 model = translation * rotation * scale * vec4(position, 1.0f);
    gl_Position = projection * view * model;
}