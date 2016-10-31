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
	if (height > 0) {
		color = vec4(0, height + 0.2f , 0, 1.0f);
	} else {
		color = vec4(0, -height + 0.2f, 0, 1.0f);
	}

}

