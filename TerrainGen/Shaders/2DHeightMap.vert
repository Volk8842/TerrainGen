#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 modification;
uniform mat4 projection;

out float height;

void main()
{
	vec4 model = modification * vec4(position.xz, 0.0f, 1.0f);
    gl_Position = projection * model;
	height = position.y;
}