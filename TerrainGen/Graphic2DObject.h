#ifndef GRAPHIC_2D_OBJECT_H
#define GRAPHIC_2D_OBJECT_H

#include <vector>
#include "opengl.h"
#include "ShaderProgram.h"
#include "Scene.h"

class Scene;

class Graphic2DObject
{
public:
	Graphic2DObject(Scene* scene);

	virtual void setVertices() = 0;
	void render();
	void prepareToRender();

	void setShaderProgram(ShaderProgram* shaderProgram);

protected:
	Scene* m_scene;
	ShaderProgram* m_shaderProgram;

	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject;
	GLuint m_elementBufferObject;
	
	std::vector<GLfloat>* m_vertices;
	std::vector<GLuint>* m_indices;

	bool m_prepareToRenderNeeded;
};

#endif //GRAPHIC_2D_OBJECT_H