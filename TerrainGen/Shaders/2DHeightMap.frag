#version 330 core

in float height;

out vec4 color;

void main()
{
//if (height < 0.4f)
//{
//	color = vec4(height * 0.8f, height * 0.8f, height * 2.5f, 1.0f);
//}
//else if (height < 0.5f)
//{
//	color = vec4(height + 0.2f, height + 0.1f, 0.2f, 1.0f);
//}
//else if (height < 0.6f)
//{
//	color = vec4(0.0f, height - 0.3f, 0.0f, 1.0f);
//}
//else if (height < 0.8f)
//{
//	color = vec4(height - 0.2f, height - 0.2f, height - 0.2f, 1.0f);
//}
//else
	color = vec4(height, height, height, 1.0f);
}