#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <vector>
#include "opengl.h"
#include "ShaderProgram.h"

class GraphicObject
{
public:
	GraphicObject();
	void draw();

private:
	void prepareToDraw();

	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;
	GLuint m_elementBufferObject;

	ShaderProgram* m_shaderProgram;

	std::vector<GLfloat> m_vertices;
	std::vector<GLuint> m_indices;

};

#endif //GRAPHICOBJECT_H