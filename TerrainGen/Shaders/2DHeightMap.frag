#version 330 core

in float height;

out vec4 color;

void main()
{
	float dHeight;
	if (height < 0.3f) {
		color = vec4(height * 0.5f, height, height * 3, 1.0f);
	}
	else if (height < 0.5f) {
		dHeight = height - 0.3f;
		color = vec4(0.1f + dHeight * 2, 0.3f, 0.9f - dHeight * 4, 1.0f);
	}
	else if (height < 0.6f) {
		dHeight = height - 0.5f;
		color = vec4(0.5f + dHeight * 2, 0.3f + dHeight * 2, 0.1f, 1.0f);
	}
	else if (height < 0.7f) {
		dHeight = height - 0.6f;
		color = vec4(0.7f - dHeight * 6f, 0.5f - dHeight * 2, 0.1f, 1.0f);
	}
	else if (height < 0.8f) {
		dHeight = height - 0.7f;
		color = vec4(0.4f + dHeight * 4, 0.4f + dHeight * 4, 0.4f + dHeight * 4, 1.0f);
	}
	else
		color = vec4(height, height, height, 1.0f);
}