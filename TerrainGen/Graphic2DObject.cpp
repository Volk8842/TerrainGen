#include <Graphic2DObject.h>
#include <CameraManager.h>

Graphic2DObject::Graphic2DObject(std::vector<GLfloat>* vertices,
								 std::vector<GLuint>* indices
								 ) :
m_vertices(vertices),
m_indices(indices) {
	m_dataUpdated = true;
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->compileShaderProgram("2DHeightMap.vert", "2DHeightMap.frag");
}

Graphic2DObject::~Graphic2DObject() {
	delete(m_vertices);
	delete(m_indices);
}

void Graphic2DObject::prepareToRender() {
	if (!m_dataUpdated)
		return;
	m_dataUpdated = false;
	glGenVertexArrays(1, &m_vertexArrayObject);
	glGenBuffers(1, &m_vertexBufferObject);
	glGenBuffers(1, &m_elementBufferObject);

	glBindVertexArray(m_vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertices->size(), &m_vertices->front(), GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices->size(), &m_indices->front(), GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Graphic2DObject::render() {
	m_shaderProgram->use();

	glm::mat4 translation(1.0f);
	glm::mat4 rotation(1.0f);
	glm::mat4 scale(1.0f);

	glm::mat4 view = CameraManager::getInstance()->getCamera()->getViewMatrix();

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

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
	glDrawElements(GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void Graphic2DObject::setShaderProgram(ShaderProgram* shaderProgram) {
	m_shaderProgram = shaderProgram;
}
