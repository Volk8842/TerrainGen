#version 330 core

in vec3 outPosition;

out vec4 color;

void main()
{
    float height = sqrt(outPosition.x * outPosition.x + outPosition.y * outPosition.y + outPosition.z * outPosition.z);
	height = (height * 100 - 90) / 10;
	color = vec4(height, height, height, 1.0f);
}

