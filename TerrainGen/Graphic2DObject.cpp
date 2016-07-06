#include "Graphic2DObject.h"

Graphic2DObject::Graphic2DObject(Scene* scene)
{
	m_scene = scene;
	m_prepareToRenderNeeded = true;
}

void Graphic2DObject::prepareToRender()
{
	if (!m_prepareToRenderNeeded)
		return;
	m_prepareToRenderNeeded = false;
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

void Graphic2DObject::render()
{
	m_shaderProgram->use();

	glm::vec2 position(320.0f, 240.0f);
	glm::vec2 scale(10.0f, 10.0f);  
	GLfloat rotate(0.0f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(scale, 1.0f));

	glm::mat4 projection = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
	GLint projectionLoc = glGetUniformLocation(m_shaderProgram->program(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint modificationLoc = glGetUniformLocation(m_shaderProgram->program(), "modification");
	glUniformMatrix4fv(modificationLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Graphic2DObject::setShaderProgram(ShaderProgram* shaderProgram)
{
	m_shaderProgram = shaderProgram;
}
