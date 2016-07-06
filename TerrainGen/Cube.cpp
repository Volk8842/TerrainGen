#include "Cube.h"

Cube::Cube()
{
	m_vertices = {
		0.5f, 0.5f, 0.5f, 0.6f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.3f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.3f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.3f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.3f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.3f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.3f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.3f, 0.0f, 0.0f,
	};
	m_indices = {
		0, 1, 3,
		1, 2, 3,
		1, 5, 2,
		5, 6, 2,
		4, 5, 0,
		5, 1, 0,
		4, 5, 7,
		5, 6, 7,
		4, 0, 7,
		0, 3, 7,
		3, 2, 7,
		2, 6, 7,
	};
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->compileShaderProgram("vertex.vsh", "fragment.fsh");
	setShaderProgram(m_shaderProgram);
	initVAOData();
}