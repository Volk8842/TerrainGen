#include "GraphicObject.h"
#include "ShaderProgram.h"

GraphicObject::GraphicObject()
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
	m_shaderProgram->compileShaderProgram("vertex.vert", "fragment.frag");

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

void GraphicObject::draw()
{
	m_shaderProgram->use();

	glm::mat4 translation(1.0f);
	glm::mat4 rotation(1.0f);
	glm::mat4 scale(1.0f);
	glm::mat4 view;
	glm::mat4 projection;

	view = glm::lookAt(
		glm::vec3(2, 2, 2), // Camera is at (2,2,2), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	GLint translationLoc = glGetUniformLocation(m_shaderProgram->program(), "translation");
	GLint rotationLoc = glGetUniformLocation(m_shaderProgram->program(), "rotation");
	GLint scaleLoc = glGetUniformLocation(m_shaderProgram->program(), "scale");
	GLint viewLoc = glGetUniformLocation(m_shaderProgram->program(), "view");
	GLint projectionLoc = glGetUniformLocation(m_shaderProgram->program(), "projection");

	glUniformMatrix4fv(translationLoc, 1, GL_FALSE, glm::value_ptr(translation));
	glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, glm::value_ptr(rotation));
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scale));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}