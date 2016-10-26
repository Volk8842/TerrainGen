#version 330 core

in float height;

out vec4 color;

float col(float a, float b, float dHeight, float dX) {
	return a + (b - a) / dHeight * dX;
}

vec4 colored(float r1, float g1, float b1, float r2, float g2, float b2, float dHeight, float dX) {
	return vec4(col(r1, r2, dHeight, dX),
				col(g1, g2, dHeight, dX),
				col(b1, b2, dHeight, dX),
				1.0f);
}

void main()
{
	float dHeight;
	if (height < 0.3f) {
		color = colored(0.0f, 0.0f, 0.0f, 0.4f, 0.6f, 0.9f, 0.3f, height);
	}
	else if (height < 0.4f) {
		dHeight = height - 0.3f;
		color = colored(0.5f, 0.3f, 0.1f, 0.7f, 0.5f, 0.1f, 0.1f, dHeight);
	}
	else if (height < 0.5f) {
		dHeight = height - 0.4f;
		color = colored(0.7f, 0.5f, 0.1f, 0.1f, 0.3f, 0.1f, 0.1f, dHeight);
	}
	else if (height < 0.6f) {
		dHeight = height - 0.5f;
		color = colored(0.1f, 0.3f, 0.1f, 0.2f, 0.5f, 0.1f, 0.1f, dHeight);
	}
	else if (height < 0.7f) {
		dHeight = height - 0.6f;
		color = colored(0.2f, 0.5f, 0.1f, 0.2f, 0.2f, 0.2f, 0.1f, dHeight);
	}
	else if (height < 0.8f) {
		dHeight = height - 0.7f;
		color = colored(0.2f, 0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 0.1f, dHeight);
	}
	else
		color = vec4(height, height, height, 1.0f);
}

