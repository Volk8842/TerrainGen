#version 330 core

in float height;

out vec4 color;

void main()
{
	if (height < 0.4f) 
	{
		color = vec4(0.0f, 0.0f, height + 0.3f, 1.0f);
	} 
	else if (height < 0.7f)
	{
		color = vec4(0.0f, height, 0.0f, 1.0f);
	} 
	else 
		color = vec4(height, height, height, 1.0f);
}