#ifndef GRAPHIC_2D_OBJECT_H
#define GRAPHIC_2D_OBJECT_H

#include <vector>
#include <opengl.h>
#include <ShaderProgram.h>

class Graphic2DObject
{
public:
	Graphic2DObject(std::vector<GLfloat>* vertices,
					std::vector<GLuint>* indices);
	~Graphic2DObject();

	void render();
	void prepareToRender();

	void setShaderProgram(ShaderProgram* shaderProgram);

protected:
	ShaderProgram* m_shaderProgram;

	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;
	GLuint m_elementBufferObject;
	
	std::vector<GLfloat>* m_vertices;
	std::vector<GLuint>* m_indices;

	bool m_dataUpdated;
};

#endif //GRAPHIC_2D_OBJECT_H