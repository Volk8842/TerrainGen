#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 modification;
uniform mat4 projection;

out vec3 ver_color;

void main()
{
	vec4 model = modification * vec4(position.xy, 0.0f, 1.0f);
    gl_Position = projection * model;
	ver_color = vec3(position.z, position.z, position.z);
}