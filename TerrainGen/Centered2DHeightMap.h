#ifndef CENTERED_2D_HEIGHT_MAP_H
#define CENTERED_2D_HEIGHT_MAP_H

#include <array>
#include "opengl.h"

// because there is no const float shit
#define UNDEFINED_VALUE -1.0f

class Centered2DHeightMap
{
public:
	Centered2DHeightMap();
	~Centered2DHeightMap();
	void setVertex(int x, int y, GLfloat value);
	GLfloat vertex(int x, int y);

	static const int SECTOR_SIDE_WIDTH = 9;
	static const int SECTOR_HALF_SIDE_WIDTH = (SECTOR_SIDE_WIDTH - 1) / 2;
	static const int SECTOR_SIZE = SECTOR_SIDE_WIDTH * SECTOR_SIDE_WIDTH;

private:
	std::array<GLfloat, SECTOR_SIZE>* m_array;

};

#endif //CENTERED_2D_HEIGHT_MAP_H
