#ifndef CENTERED_2D_HEIGHT_MAP_H
#define CENTERED_2D_HEIGHT_MAP_H

#include <vector>
#include "opengl.h"

class Centered2DHeightMap
{
public:
	Centered2DHeightMap(int size);
	~Centered2DHeightMap();
	void setVertex(int x, int y, GLfloat value);
	GLfloat vertex(int x, int y);

private:
	std::vector<GLfloat>* m_vector;

};

#endif //CENTERED_2D_HEIGHT_MAP_H
