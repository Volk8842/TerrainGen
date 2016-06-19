#include "GraphicObject.h"
#include "ShaderProgram.h"

GraphicObject::GraphicObject()
{
	m_vertices = {
		0.5f, 0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f, 0.5f, 0.0f   // Top Left 
	};
	m_indices = {
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->compileShaderProgram();

	prepareToDraw();
}

void GraphicObject::prepareToDraw()
{
	glGenVertexArrays(1, &m_vertexArrayObject);
	glGenBuffers(1, &m_vertexBufferObject);
	glGenBuffers(1, &m_elementBufferObject);

	glBindVertexArray(m_vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertices.size(), &m_vertices[0], GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices.size(), &m_indices[0], GL_STREAM_DRAW);

	//TODO: must be customizable
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

void GraphicObject::draw()
{
	m_shaderProgram->use();
	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}